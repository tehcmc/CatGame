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

	if (ItemPool.Num() != 0) //make sure array is not empty
	{
		int selectedProp = FMath::RandRange(0, ItemPool.Num() - 1);

		spawnItem = ItemPool[selectedProp];
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("Array size %i"), selectedProp));
		itemspawn = GetWorld()->SpawnActor<AItemBase>(spawnItem, GetComponentLocation(), myRot);

	}
	

	// ...
	
}


// Called every frame
void USpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

