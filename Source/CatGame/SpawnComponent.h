// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ItemBase.h"

#include "SpawnComponent.generated.h"





UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATGAME_API USpawnComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<class AItemBase> spawnItem;

//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
//	class USphereComponent* SpawnArea;


	UPROPERTY(EditAnywhere, Category = "Config")
	SpawnType SpawnerSize = SpawnType::IT_Med;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
