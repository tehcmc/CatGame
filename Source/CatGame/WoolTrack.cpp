// Fill out your copyright notice in the Description page of Project Settings.

#include "WoolTrack.h"
#include "Components/SplineComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SplineMeshComponent.h"

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
	
	//PopulateSplinePoints();


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
			tempSphere->SetSphereRadius(20.f);
			tempSphere->SetVisibility(true);
			tempSphere->SetHiddenInGame(false);

			tempSphere->AttachToComponent(SplineComponent, rules);
			SplinePoints.Add(tempSphere);



			tempComp = NewObject<USplineMeshComponent>(this);
			tempComp->SetStaticMesh(SplineStaticMesh);
		//	tempComp->GetForwardAxis(MeshAxis,true);
			tempComp->SetStartAndEnd(startloc,endloc,startTan,endTan,true);
			

			splineMeshComp.Add(tempComp);


		}
		
		return true;
	}
	return false;
}

// Called every frame
void AWoolTrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

