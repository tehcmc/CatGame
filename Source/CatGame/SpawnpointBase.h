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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Config")
		AItemBase* spawnItem;

	UPROPERTY(EditAnywhere, Category = "Config")
	SpawnType SpawnerSize = SpawnType::IT_Med;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
