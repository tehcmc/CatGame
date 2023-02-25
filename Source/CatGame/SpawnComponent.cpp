// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnComponent.h"
#include "Components/SphereComponent.h"
// Sets default values for this component's properties
USpawnComponent::USpawnComponent()
{

}


// Called when the game starts
void USpawnComponent::BeginPlay()
{
	FRotator myRot(0, 0, 0);
	FVector myLoc(0, 0, 0);
	FActorSpawnParameters ActorSpawnParams;
	Super::BeginPlay();
	AItemBase* itemspawn =nullptr;
	itemspawn = GetWorld()->SpawnActor<AItemBase>(spawnItem, GetComponentLocation(), myRot);

	// ...
	
}


// Called every frame
void USpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

