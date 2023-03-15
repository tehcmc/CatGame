// Fill out your copyright notice in the Description page of Project Settings.

#include "WoolTrack.h"
#include "Components/SplineComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SplineMeshComponent.h"
#include "RollerBall.h"

// Sets default values
AWoolTrack::AWoolTrack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	SplineComponent->SetupAttachment(RootComponent);




}

// Called when the game starts or when spawned
void AWoolTrack::BeginPlay()
{
	Super::BeginPlay();
	int arrayEnd = SplinePoints.Num() - 1;
	for (int i = arrayEnd; i >= 0; i--)
	{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("Array Entry: %i"), i));
	SplinePoints[i]->OnComponentBeginOverlap.AddDynamic(this, &AWoolTrack::OverlapBegin);
	SplinePoints[i]->OnComponentEndOverlap.AddDynamic(this, &AWoolTrack::OverlapEnd);

	}




}


bool AWoolTrack::PopulateSplinePoints()
{

	//	Set up spline points in game
	//	get spline point count
	//	 spawn sphere collider on each spline point
	//	populate sphere collider array with spawned spheres
	//  when ball collides with collider at array entry i delete spline point i (i -1 if that looks better
	



	if (SplineComponent)
	{
		//										location						rotation					scale				     weld
		splineMeshComp.Empty();
		SplinePoints.Empty();


		FAttachmentTransformRules rules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
		for (int i = 0; i < SplineComponent->GetNumberOfSplinePoints()-2; i++)
		{
			USplineMeshComponent* tempComp;
			USphereComponent* tempSphere;

			FVector startloc = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
			FVector endloc = SplineComponent->GetLocationAtSplinePoint(i+1, ESplineCoordinateSpace::Local);

			FVector startTan = SplineComponent->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
			FVector endTan = SplineComponent->GetTangentAtSplinePoint(i+1, ESplineCoordinateSpace::Local);
			
			tempSphere = NewObject<USphereComponent>(this);
			tempSphere->SetRelativeLocation(endloc);
			tempSphere->SetSphereRadius(200.f);
			tempSphere->SetVisibility(true);
			tempSphere->SetHiddenInGame(false);

			tempSphere->AttachToComponent(SplineComponent, rules);
			SplinePoints.Add(tempSphere);



			tempComp = NewObject<USplineMeshComponent>(this);
			tempComp->SetStaticMesh(SplineStaticMesh);
			tempComp->SetForwardAxis(ESplineMeshAxis::Z,true);
			tempComp->SetStartAndEnd(startloc, startTan, endloc,endTan,true);
			

			splineMeshComp.Add(tempComp);


		}
		
		return true;
	}
	return false;
}



void AWoolTrack::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARollerBall* tempBall = Cast<ARollerBall>(OtherActor);
	USphereComponent* tempPoint = Cast<USphereComponent>(OverlappedComponent);
	int arrayEnd = SplinePoints.Num() - 1;
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("Array Size: %i"), SplinePoints.Num() - 1));
	for (int i = arrayEnd; i >=0; i--)
	{
	
		if (SplinePoints[i] && tempPoint == SplinePoints[i])
		{
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("Array Entry: %i"), i));
			if (splineMeshComp[i] && !splineMeshComp[i]->IsVisible()&& tempPoint!= SplinePoints[arrayEnd])
			{

				//attach rope to point, add rope first lol

				splineMeshComp[i+1]->SetVisibility(false);
				SplinePoints[i]->SetCollisionEnabled(ECollisionEnabled::NoCollision);

				tempBall->SetActorRelativeScale3D(tempBall->GetActorRelativeScale3D()+scaleInc);

			

				
			}
			else if (tempPoint == SplinePoints[arrayEnd] && !splineMeshComp[i]->IsVisible())
			{

				GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("LAST CCOMP")));
				SplinePoints[i]->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				tempBall->SetActorRelativeScale3D(tempBall->GetActorRelativeScale3D() + scaleInc);
				SetLifeSpan(0.1f);
				Destroy();

			}
		}
		

	}

}

void AWoolTrack::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AWoolTrack::OnConstruction(const FTransform& Transform)
{
//	PopulateSplinePoints();
	
}

// Called every frame
void AWoolTrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

