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

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
ACatBase::ACatBase()
{
	PushSphere = CreateDefaultSubobject<USphereComponent>("PushSphere");
	PushSphere->SetSphereRadius(200.f);
	PushSphere->SetCollisionProfileName("OverlapAll");
	PushSphere->SetupAttachment(GetRootComponent());
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
				Primitive->AddImpulse(PushDirection * PushForce, NAME_None, true);
			}
		}
		
	}

}



void ACatBase::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, FString::Printf(TEXT("Interact")));

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


