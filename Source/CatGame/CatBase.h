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
	ACatBase();

		/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;
	/** Jump Input Action */
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		class UNiagaraSystem* Particles;

	UPROPERTY(EditAnywhere, Category = "Config")
	float PushForce = 1000.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USphereComponent* PushSphere;

virtual void BeginPlay() override;

void Attack();

void Interact();

virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
