// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractibleBase.generated.h"

UCLASS()
class CATGAME_API AInteractibleBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractibleBase();

	void Interact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnInteract();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
