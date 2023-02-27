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
	float pushForce = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Config")
	float interactRange = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USphereComponent* PushSphere;

	// cat's mouth, used to attach pickups, also origin for line trace
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USphereComponent* MouthAttachment;

	FCollisionQueryParams Parameters;

	virtual void BeginPlay() override;

void Attack();

virtual void Tick(float DeltaTime) override;

void PickUp();



void Interact();

virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


bool LineTraceMethod(FHitResult& OutHit);


public:



	class USphereComponent* GetMouthAttachment() const { return MouthAttachment; }
	void SetMouthAttachment(class USphereComponent* val) { MouthAttachment = val; }
};
