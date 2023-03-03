// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractibleBase.h"
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


	UFUNCTION(BlueprintCallable, Category = "Cat Ref")
	class ACatBase* GetCatReference() const { return catReference; }

	UFUNCTION(BlueprintCallable, Category = "Cat ref")
	void SetCatReference(class ACatBase* val) { catReference = val; }

public:
	virtual void BeginPlay() override;
	void PickUp(class ACatBase* catRef);
	void Drop(class ACatBase* catRef);
	
	class UPostProcessComponent* GetOutlineComponent() const { return OutlineComponent; }

	void SetOutlineComponent(class UPostProcessComponent* val) { OutlineComponent = val; }

	UFUNCTION(BlueprintCallable, Category = "Config")

	bool GetPickedUp() const { return pickedUp; }

	UFUNCTION(BlueprintCallable, Category = "Config")

	void SetPickedUp(bool val) { pickedUp = val; }


protected:


UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
void OnDropped();

class ACatBase* catReference;

UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
void OnPickup();

bool pickedUp;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
UStaticMeshComponent* MeshComponent;
UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
class UPostProcessComponent* OutlineComponent;


};
