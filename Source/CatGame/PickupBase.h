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
	

protected:
void OnPickup();


};
