// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CatGameCharacter.h"
#include "InteractibleBase.h"
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
	class UInputAction* DropAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;
	/** Jump Input Action */
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
	class UNiagaraSystem* Particles;

	UPROPERTY(EditAnywhere, Category = "Config")
	float pushForce = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Config")
	float sprintMultiplier = 1.5f;

	UPROPERTY(EditAnywhere, Category = "Config")
	float interactRange = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USphereComponent* PushSphere;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* itemRefMesh;

	// cat's mouth, used to attach pickups, also origin for line trace
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USphereComponent* MouthAttachment;

	int score =0;
	TArray<AActor*> AttachedActors;


	FCollisionQueryParams Parameters;

	virtual void BeginPlay() override;

	void Attack();

	virtual void Tick(float DeltaTime) override;

	void StartSprint();

	void StopSprint();

	class APickupBase* itemRef=nullptr;
	float FindClosestPickup();

	void DropItem();

	float DistanceBetween(AActor* A, AActor* B);

	float defaultSpeed = 0;


void Interact();

virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


bool LineTraceMethod(FHitResult& OutHit);


public:



	class USphereComponent* GetMouthAttachment() const { return MouthAttachment; }
	void SetMouthAttachment(class USphereComponent* val) { MouthAttachment = val; }


	class UStaticMeshComponent* GetItemRefMesh() const { return itemRefMesh; }
	void SetItemRefMesh(class UStaticMeshComponent* val) { itemRefMesh = val; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void InteractPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void DropPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void ScoreChanged();


	UFUNCTION(BlueprintCallable, Category = "Config")
	TArray<AActor*> GetAttachedActorsForBP(){return AttachedActors; }

	UFUNCTION(BlueprintCallable, Category = "Config")
	void PickUpItem(class APickupBase* pickupTemp);

	UFUNCTION(BlueprintCallable, Category = "Score")
	int GetScore() const { return score; }
	UFUNCTION(BlueprintCallable, Category = "Score")
	void SetScore(int val); 
};
