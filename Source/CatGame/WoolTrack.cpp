// Fill out your copyright notice in the Description page of Project Settings.

#include "WoolTrack.h"
#include "Components/SplineComponent.h"
#include "Components/SphereComponent.h"


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
	
	PopulateSplinePoints();


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
		SplinePoints.SetNum(SplineComponent->GetNumberOfSplinePoints());
		//										location						rotation					scale				     weld

		FAttachmentTransformRules rules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, false);
		for (int i = 0; i < SplineComponent->GetNumberOfSplinePoints(); i++)
		{
			FVector WLoc = SplineComponent->GetLocationAtSplinePoint(i,ESplineCoordinateSpace::Local);

			GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Yellow, FString::Printf(TEXT("X Coord %f"), WLoc.X));
			GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Yellow, FString::Printf(TEXT("Y Coord %f"), WLoc.Y));

			SplinePoints[i] = NewObject<USphereComponent>(this);
			SplinePoints[i]->AttachToComponent(SplineComponent,rules);
			SplinePoints[i]->SetRelativeLocation(WLoc);
			SplinePoints[i]->SetSphereRadius(200.f);
			SplinePoints[i]->SetVisibility(true);
			SplinePoints[i]->SetHiddenInGame(false);
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

