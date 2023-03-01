// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
// Sets default values for this component's properties
USpawnComponent::USpawnComponent()
{

}


// Called when the game starts
void USpawnComponent::BeginPlay()
{
	Super::BeginPlay();
	SetupSpawnPool();

}


bool USpawnComponent::SetupSpawnPool()
{
	

	FRotator myRot(0, 0, 0);
	FVector myLoc(0, 0, 0);
	FActorSpawnParameters ActorSpawnParams;


	

	TArray<AActor*> itempoolTemp;

	//get all actors of the flashback object class in the game world and store them in the pointer array.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemPool::StaticClass(), itempoolTemp);
	
	if (!itempoolTemp.IsEmpty())
	{
		ItemPoolRef = Cast<AItemPool>(itempoolTemp[0]);
	

		spawnPool = ItemPoolRef->GetItemPool();

		if (!spawnPool.IsEmpty()) //make sure array is not empty
		{
		
			for (int i = 0; i < spawnPool.Num()-1; i++)
			{
				
				AItemBase* itemspawn = ItemPoolRef->GetItemAt(i);
				if (itemspawn && itemspawn->GetItemSize() != SpawnerSize)
				{
					spawnPool.RemoveAt(i);
				}
				
			}

			int selectedProp = FMath::RandRange(0, spawnPool.Num() - 1);

			spawnItem = spawnPool[selectedProp];
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("Array size %i"), selectedProp));
			GetWorld()->SpawnActor<AItemBase>(spawnItem, GetComponentLocation(), myRot);
			return true;
		}
		return false;
		

	}
	return false;
	
}
  
// Called every frame
void USpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

