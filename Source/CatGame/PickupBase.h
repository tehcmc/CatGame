// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractibleBase.h"
#include "CatBase.h"
#include "PickupBase.generated.h"


/**
 * 
 */
UCLASS()
class CATGAME_API APickupBase : public AInteractibleBase
{
	GENERATED_BODY()
public:
	APickupBase();



public:
	virtual void BeginPlay() override;
	void PickUp(ACatBase* catRef);
	void Drop(ACatBase* catRef);
	
	class UPostProcessComponent* GetOutlineComponent() const { return OutlineComponent; }
	void SetOutlineComponent(class UPostProcessComponent* val) { OutlineComponent = val; }
	UFUNCTION(BlueprintCallable, Category = "Config")
	bool GetPickedUp() const { return pickedUp; }
	UFUNCTION(BlueprintCallable, Category = "Config")
	void SetPickedUp(bool val) { pickedUp = val; }


protected:
UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
void OnDropped();

UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
void OnPickup();

bool pickedUp;

UPROPERTY(EditAnywhere, Category = "Config")
UStaticMeshComponent* MeshComponent;
UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
class UPostProcessComponent* OutlineComponent;


};
