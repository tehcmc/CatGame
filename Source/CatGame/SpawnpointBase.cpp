// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnpointBase.h"

#include "ItemPool.h"
#include "Kismet/GameplayStatics.h"

//	spawn point base
//  attach to furniture blueprints to allow for randomized spawns
//	also used as a score incrementer, object leaves spawn bounds, increment score
// 
// Sets default values
ASpawnpointBase::ASpawnpointBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASpawnpointBase::BeginPlay()
{
	Super::BeginPlay();
	
	SetupSpawnPool();
}


bool ASpawnpointBase::SetupSpawnPool()
{


	FRotator myRot(0, 0, 0);
	FVector myLoc(0, 0, 0);
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.Owner = this;



	TArray<AActor*> itempoolTemp;

	//get all actors of the flashback object class in the game world and store them in the pointer array.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemPool::StaticClass(), itempoolTemp);

	if (!itempoolTemp.IsEmpty() && !manualSpawn)
	{
		ItemPoolRef = Cast<AItemPool>(itempoolTemp[0]);


		spawnPool = ItemPoolRef->GetItemPool();

		if (!spawnPool.IsEmpty()) //make sure array is not empty
		{

			for (int i = 0; i < spawnPool.Num() - 1; i++)
			{

				AItemBase* itemspawn = ItemPoolRef->GetItemAt(i);
				if (itemspawn && itemspawn->GetItemSize() != SpawnerSize)
				{
					spawnPool.RemoveAt(i);
				}

			}

			int selectedProp = FMath::RandRange(0, spawnPool.Num() - 1);

			spawnItem = spawnPool[selectedProp];

			AItemBase* tempActor;
			tempActor = GetWorld()->SpawnActor<AItemBase>(spawnItem, GetActorLocation(), myRot);
			tempActor->SetOwner(this);

			return true;
		}
		return false;

	}
	else if (spawnItem)
	{
		AItemBase* tempActor;
		tempActor = GetWorld()->SpawnActor<AItemBase>(spawnItem, GetActorLocation(), myRot);
		tempActor->SetOwner(this);
	}
	return false;

}

void ASpawnpointBase::RespawnItem()
{
	FRotator myRot(0, 0, 0);
	FVector myLoc(0, 0, 0);
	FActorSpawnParameters ActorSpawnParams;	
	ActorSpawnParams.Owner = this;
	if (respawnable && GetWorld())
	{
		OnItemDestroyed();
		AItemBase* tempActor;
	
		tempActor = GetWorld()->SpawnActor<AItemBase>(spawnItem, GetActorLocation(), myRot);
		tempActor->SetOwner(this);
	}

}

void ASpawnpointBase::OnItemDestroyed_Implementation()
{

}

// Called every frame
void ASpawnpointBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}