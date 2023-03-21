// Fill out your copyright notice in the Description page of Project Settings.


#include "RollerBall.h"


#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/CollisionProfile.h" 	
#include "CableComponent.h"
#include "Engine/StaticMesh.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


ARollerBall::ARollerBall()
{
	// Create mesh component for the ball
	Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball0"));
	Ball->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	Ball->SetSimulatePhysics(true);
	Ball->SetAngularDamping(0.1f);
	Ball->SetLinearDamping(0.1f);
	Ball->BodyInstance.MassScale = 3.5f;
	Ball->BodyInstance.MaxAngularVelocity = 800.0f;
	Ball->SetNotifyRigidBodyCollision(true);


	// Create mesh component for the ball
	StaticBall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Ball"));
	StaticBall->BodyInstance.SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	StaticBall->SetSimulatePhysics(false);
	StaticBall->SetNotifyRigidBodyCollision(true);
	StaticBall->SetupAttachment(Ball);

	CamAttachPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Camera attach point"));
	CamAttachPoint->BodyInstance.SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	CamAttachPoint->SetSimulatePhysics(false);
	CamAttachPoint->SetNotifyRigidBodyCollision(true);
	CamAttachPoint->SetupAttachment(StaticBall);

	woolString = CreateDefaultSubobject<UCableComponent>(TEXT("Wool String"));
	woolString->SetupAttachment(StaticBall);
	woolString->SetVisibility(false);


	EntrySphere = CreateDefaultSubobject<USphereComponent>("EntrySphere");
	EntrySphere->SetSphereRadius(200.f);
	EntrySphere->SetCollisionProfileName("OverlapAll");
	EntrySphere->SetupAttachment(StaticBall);

	// Create a camera boom attached to the root (ball)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(CamAttachPoint);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true); // Rotation of the ball should not affect rotation of boom
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 1200.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 3.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // We don't want the controller rotating the camera
	defaultMult = 1;

	RollTorque = 50000000.0f;
	JumpImpulse = 350000.0f;
	bCanJump = true;



}


void ARollerBall::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{

		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Triggered, this, &ARollerBall::MoveForward);
		EnhancedInputComponent->BindAction(SideRollAction, ETriggerEvent::Triggered, this, &ARollerBall::MoveRight);
		EnhancedInputComponent->BindAction(BounceAction, ETriggerEvent::Started, this, &ARollerBall::Jump);
		EnhancedInputComponent->BindAction(ExitAction,ETriggerEvent::Started,this,&ARollerBall::ExitPressed);
		EnhancedInputComponent->BindAction(SpeedUpAction, ETriggerEvent::Started, this, &ARollerBall::StartSpeedUp);
		EnhancedInputComponent->BindAction(SpeedUpAction, ETriggerEvent::Completed, this, &ARollerBall::StopSpeedUp);

	}
}

void ARollerBall::ExitPressed_Implementation()
{

}

void ARollerBall::MoveRight(const FInputActionValue& Value)
{
	const float DirVal = Value.Get<float>();
	float Val = DirVal;
	FVector testVec = Camera->GetForwardVector();

	FVector rollDir = testVec * Val;
	if (Ball->GetPhysicsAngularVelocityInDegrees().Length() < maxSpeed)
	{
		Ball->AddTorqueInRadians(-(rollDir *(RollTorque * defaultMult)), TEXT("None"), true);
	}

}

void ARollerBall::MoveForward(const FInputActionValue& Value)
{

 	FVector2D MovementVector = Value.Get<FVector2D>();

	const float DirVal = Value.Get<float>();
	float Val = DirVal;
	FVector testVec = Camera->GetRightVector();

	FVector rollDir = testVec*Val;
	if (Ball->GetPhysicsAngularVelocityInDegrees().Length() < maxSpeed)
	{
		Ball->AddTorqueInRadians(rollDir * (RollTorque * defaultMult), TEXT("None"), true);
	}
	
}

void ARollerBall::Jump()
{
	if (bCanJump)
	{
		const FVector Impulse = FVector(0.f, 0.f, JumpImpulse);
		Ball->AddImpulse(Impulse);
		bCanJump = false;
	}
}


void ARollerBall::StartSpeedUp()
{

defaultMult = torqueMultiplier;

}


void ARollerBall::StopSpeedUp()
{

defaultMult = 1.f;

}


void ARollerBall::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	bCanJump = true;
}





