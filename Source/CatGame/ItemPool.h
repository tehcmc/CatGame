// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.h"
#include "ItemPool.generated.h"

UCLASS()
class CATGAME_API AItemPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Config")
	TArray<TSubclassOf<class AItemBase>> ItemPool;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	TArray<TSubclassOf<class AItemBase>> GetItemPool() const { return ItemPool; }

	class AItemBase* GetItemAt(int i){ return Cast<AItemBase>(ItemPool[i]); }

	void SetItemPool(TArray<TSubclassOf<class AItemBase>> val) { ItemPool = val; }


};
