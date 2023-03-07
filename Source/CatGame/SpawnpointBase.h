// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.h"

#include "SpawnpointBase.generated.h"



UCLASS()
class CATGAME_API ASpawnpointBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnpointBase();

	

protected:

	virtual void BeginPlay() override;



	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<class AItemBase> spawnItem;

	UPROPERTY(BlueprintReadWrite)
	AItemBase* spawnedItem;


	class AItemPool* ItemPoolRef;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<AItemBase>>spawnPool;
	//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	//	class USphereComponent* SpawnArea;


	UPROPERTY(EditAnywhere, Category = "Config")
		SpawnType SpawnerSize = SpawnType::IT_Med;

	UPROPERTY(EditAnywhere, Category = "Config")
		bool manualSpawn = false;

	UPROPERTY(EditAnywhere, Category = "Config")
		bool respawnable = false;


	 bool SetupSpawnPool();

	



	 UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		 void OnItemDestroyed();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	 void RespawnItem();
};
