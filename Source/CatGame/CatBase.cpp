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
#include "PickupBase.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ACatBase::ACatBase()
{
	PushSphere = CreateDefaultSubobject<USphereComponent>("PushSphere");
	PushSphere->SetSphereRadius(200.f);
	PushSphere->SetCollisionProfileName("OverlapAll");
	PushSphere->SetupAttachment(GetRootComponent());

	MouthAttachment = CreateDefaultSubobject<USphereComponent>("Mouth Attachment");
	MouthAttachment->SetSphereRadius(200.f);
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

void ACatBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector startPoint = MouthAttachment->GetComponentLocation();
	FVector endpoint = (MouthAttachment->GetForwardVector() * interactRange) + startPoint;

	DrawDebugLine(GetWorld(), startPoint, endpoint, FColor(255, 0, 0), false, -1, 0, 5);

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
				tempActor->OnHit();
				float randPush;
				randPush= FMath::RandRange(pushForce, (pushForce*1.5f));

				Primitive->AddImpulse(PushDirection * pushForce, NAME_None, true);
			}
		}
		
	}

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
		if (Cast<APickupBase>(tempInteractible))
		{
			PickUpItem(tempInteractible);
		}
		else
		{
			tempInteractible->Interact();
		}
	}
}

void ACatBase::PickUpItem(AInteractibleBase* pickupTemp)
{
	//when cat interacts with an object that can be picked up call this function
				
				APickupBase* tempPickup = Cast<APickupBase>(pickupTemp);
	 			GetAttachedActors(AttachedActors);
	 			if (AttachedActors.IsEmpty())
	 			{
					
					Parameters.AddIgnoredActor(pickupTemp);
					tempPickup->PickUp(this);
	 			}
	 			else
	 			{
					Parameters.ClearIgnoredActors();
					Parameters.AddIgnoredActor(this);
					Parameters.AddIgnoredActor(tempPickup);
					APickupBase* heldItem = Cast<APickupBase>(AttachedActors[0]);
	 				heldItem->Drop(this);

					tempPickup->PickUp(this);
	 			}



}

void ACatBase::DropItem()
{
	GetAttachedActors(AttachedActors);

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("DROP ITEM ")));
	if (!AttachedActors.IsEmpty())
	{
		APickupBase* tempPickup = Cast<APickupBase>(AttachedActors[0]);
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Yellow, tempPickup->GetFName().ToString());
		Parameters.ClearIgnoredActors();
		Parameters.AddIgnoredActor(this);
		tempPickup->Drop(this);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("No elements in attached actor array")));
	}

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

		EnhancedInputComponent->BindAction(DropAction, ETriggerEvent::Triggered, this, &ACatBase::DropItem);
	}

}


