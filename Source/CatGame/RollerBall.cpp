// Fill out your copyright notice in the Description page of Project Settings.


#include "RollerBall.h"

#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/CollisionProfile.h"
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
	RootComponent = Ball;

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



	EntrySphere = CreateDefaultSubobject<USphereComponent>("EntrySphere");
	EntrySphere->SetSphereRadius(200.f);
	EntrySphere->SetCollisionProfileName("OverlapAll");
	EntrySphere->SetupAttachment(GetRootComponent());

	// Create a camera boom attached to the root (ball)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(CamAttachPoint);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true); // Rotation of the ball should not affect rotation of boom
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 1200.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 3.f;
//	SpringArm->bUsePawnControlRotation = true;
	// Create a camera and attach to boom


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Set up forces
	RollTorque = 50000000.0f;
	JumpImpulse = 350000.0f;
	bCanJump = true; // Start being able to jump
}


void ARollerBall::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{

		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Triggered, this, &ARollerBall::MoveForward);
		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Triggered, this, &ARollerBall::MoveRight);
		EnhancedInputComponent->BindAction(BounceAction, ETriggerEvent::Started, this, &ARollerBall::Jump);
		EnhancedInputComponent->BindAction(ExitAction,ETriggerEvent::Started,this,&ARollerBall::ExitPressed);
	}
}

void ARollerBall::ExitPressed_Implementation()
{

}

void ARollerBall::MoveRight(const FInputActionValue& Value)
{
// 	FVector2D MovementVector = Value.Get<FVector2D>();
// 	float Val = MovementVector.X;
// 
// 	GetSpringArm()->GetForwardVector();
// 
// 
// 	
// 	FVector testvec = GetSpringArm()->GetForwardVector();
// 	FVector plane = FVector(0.f,0.f,1.f);
// 	
// 	FVector planeTest = FVector::VectorPlaneProject(testvec,plane);
// 	planeTest.Normalize(0.0001f);
// 
// 	const FVector Torque = FVector(planeTest.X*-torqueMultiplier, planeTest.Y*-torqueMultiplier, planeTest.Z- torqueMultiplier);
// 
// 
// 	Ball->AddTorqueInRadians(Torque);

}

void ARollerBall::MoveForward(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	const float DirVal = Value.Get<float>();

	float testval = MovementVector.X * RollTorque;
	const FVector ForwardDirection = Camera->GetRightVector();
	float Val = DirVal * RollTorque;

	

	const FVector Torque = ForwardDirection*testval;//FVector(0.f, ForwardDirection.Y * Val, 0.f);









	Ball->AddTorqueInRadians(ForwardDirection,TEXT("None"),true);


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

void ARollerBall::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	bCanJump = true;
}





