// Fill out your copyright notice in the Description page of Project Settings.


#include "CatBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ItemBase.h"
#include "InteractibleBase.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ACatBase::ACatBase()
{
	PushSphere = CreateDefaultSubobject<USphereComponent>("PushSphere");
	PushSphere->SetSphereRadius(200.f);
	PushSphere->SetCollisionProfileName("OverlapAll");
	PushSphere->SetupAttachment(GetRootComponent());

	MouthAttachment = CreateDefaultSubobject<USphereComponent>("Mouth Attachment");
	MouthAttachment->SetSphereRadius(10.f);
	MouthAttachment->SetCollisionProfileName("OverlapAll");
	MouthAttachment->SetupAttachment(GetRootComponent());

	Parameters.AddIgnoredActor(this);
}

void ACatBase::BeginPlay()
{
	//call inherited begin play function
	Super::BeginPlay();
	//do new stuff here
	
	
}

void ACatBase::Attack()
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("ATTACKED")));

	TArray<AActor*> OverlappingActors;
	PushSphere->GetOverlappingActors(OverlappingActors);

	FVector PushDirection = GetActorForwardVector();
	

	for (AActor* Actor : OverlappingActors)
	{
		AItemBase* tempActor = Cast<AItemBase>(Actor);
		if (tempActor)
		{
			GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Yellow, tempActor->GetFName().ToString());
			UPrimitiveComponent* Primitive = tempActor->FindComponentByClass<UPrimitiveComponent>();
			if (Primitive)
			{

				float randPush;
				randPush= FMath::RandRange(pushForce, (pushForce*1.5f));

				Primitive->AddImpulse(PushDirection * pushForce, NAME_None, true);
			}
		}
		
	}

}



void ACatBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector startPoint = MouthAttachment->GetComponentLocation();
	FVector endpoint = (MouthAttachment->GetForwardVector() * interactRange) + startPoint;

	DrawDebugLine(GetWorld(),startPoint,endpoint,FColor(255, 0, 0),false, -1, 0,5);

}

void ACatBase::PickUp()
{
//when cat interacts with an object that can be picked up call this function

}

bool ACatBase::LineTraceMethod(FHitResult& OutHit)
{
		FVector startPoint = MouthAttachment->GetComponentLocation();
		FVector endpoint = (MouthAttachment->GetForwardVector() * interactRange) + startPoint;
		
		
		return GetWorld()->LineTraceSingleByChannel(OutHit, startPoint, endpoint, ECC_Visibility, Parameters);
}

void ACatBase::Interact()
{

	FHitResult checkLine;

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, FString::Printf(TEXT("Interact")));

	LineTraceMethod(checkLine);

	AInteractibleBase* tempInteractible;
	tempInteractible = Cast<AInteractibleBase>(checkLine.GetActor());

	if (tempInteractible)
	{
		tempInteractible->Interact();
		

	}
	


	//todo - line trace to interact, create new interactive class ie door, tv, some other stuff
}

void ACatBase::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		
		//Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ACatBase::Attack);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ACatBase::Interact);

	}

}


