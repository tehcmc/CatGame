// Fill out your copyright notice in the Description page of Project Settings.

#include "WoolTrack.h"

#include "Components/SplineComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SplineMeshComponent.h"
#include "CableComponent.h"
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
	//create overlap binds for each sphere collider (that represent spline points)
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
	for (int i = arrayEnd; i >=0; i--)
	{
	
		if (SplinePoints[i] && tempPoint == SplinePoints[i] && tempBall)
		{
	
			if (splineMeshComp[i] && !splineMeshComp[i]->IsVisible()&& tempPoint!= SplinePoints[arrayEnd])//if the collided point is valid & the spline mesh isn't visible (as previous point should have hidden on collision)
			{

				tempBall->GetWoolString()->SetAttachEndToComponent(SplinePoints[i+1]);//attach to next point

				tempBall->GetWoolString()->SetVisibility(true); //redundant after first collision

				splineMeshComp[i+1]->SetVisibility(false);//hide the spline mesh connected between this spline point to the next spline point


				SplinePoints[i]->SetCollisionEnabled(ECollisionEnabled::NoCollision);//disable collisions for this point
		

				tempBall->SetActorRelativeScale3D(tempBall->GetActorRelativeScale3D()+scaleInc);//increase size of ball

				PointReached(SplinePoints[i]);//call blueprint with reference to this point

			}
			else if (tempPoint == SplinePoints[arrayEnd] && !splineMeshComp[i]->IsVisible()) //if collided point is the final point in the spline
			{

				SplinePoints[i]->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				tempBall->SetActorRelativeScale3D(tempBall->GetActorRelativeScale3D() + scaleInc);
				tempBall->GetWoolString()->SetVisibility(false);
				SplineCompleted();
				
			}
		}
		

	}

}


void AWoolTrack::PointReached_Implementation(USphereComponent* IntersectedSphere)
{

}

void AWoolTrack::SplineCompleted_Implementation()
{

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

