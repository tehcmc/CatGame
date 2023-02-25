// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//wqetwetqwtqtq
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UENUM(BlueprintType)
enum class SpawnType : uint8
{
	IT_Small UMETA(DisplayName = "Small Item"),
	IT_Med UMETA(DisplayName = "Medium Item"),
	IT_Large UMETA(DisplayName = "Large Item"),
};

UCLASS()
class CATGAME_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Config")
		UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Config")
	SpawnType ItemSize = SpawnType::IT_Med;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
