// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CatGameCharacter.h"
#include "CatBase.generated.h"

/**
 * 
 */
UCLASS()
class CATGAME_API ACatBase : public ACatGameCharacter
{
	GENERATED_BODY()
	

		/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;
	/** Jump Input Action */
protected:

void Attack();

virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
