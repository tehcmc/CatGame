// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CatGameCharacter.h"
#include "GameFramework/Pawn.h"
#include "RollerBall.generated.h"

UCLASS()
class CATGAME_API ARollerBall : public ACatGameCharacter
{
	GENERATED_BODY()
		/** StaticMesh used for the ball */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ball, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Ball;

	/** Spring arm for positioning the camera above the ball */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ball, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

	/** Camera to view the ball */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ball, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

public:
	ARollerBall();

	/** Vertical impulse to apply when pressing jump */
	UPROPERTY(EditAnywhere, Category = Ball)
		float JumpImpulse;

	/** Torque to apply when trying to roll ball */
	UPROPERTY(EditAnywhere, Category = Ball)
		float RollTorque;

	/** Indicates whether we can currently jump, use to prevent double jumping */
	bool bCanJump;

protected:

	/** Called for side to side input */
	void MoveRight(const FInputActionValue& Value);

	/** Called to move ball forwards and backwards */
	void MoveForward(const FInputActionValue& Value);

	/** Handle jump action. */
	virtual void Jump() override;

	// AActor interface
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	// End of AActor interface

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void ExitPressed();


		/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RollAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* BounceAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ExitAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USphereComponent* EntrySphere;//sphere to define ball entry radius

	UPROPERTY(EditAnywhere, Category = "Config")
	float torqueMultiplier=1.f;

public:
	/** Returns Ball subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBall() const { return Ball; }
	/** Returns SpringArm subobject **/
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
};








