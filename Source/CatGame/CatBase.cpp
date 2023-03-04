// Fill out your copyright notice in the Description page of Project Settings.


#include "CatBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PostProcessComponent.h"


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

	PrimaryActorTick.bCanEverTick = true;

	PushSphere = CreateDefaultSubobject<USphereComponent>("PushSphere");
	PushSphere->SetSphereRadius(200.f);
	PushSphere->SetCollisionProfileName("OverlapAll");
	PushSphere->SetupAttachment(GetRootComponent());

	MouthAttachment = CreateDefaultSubobject<USphereComponent>("Mouth Attachment");
	MouthAttachment->SetSphereRadius(200.f);
	MouthAttachment->SetCollisionProfileName("OverlapAll");
	MouthAttachment->SetupAttachment(GetMesh(), TEXT("Head1Socket"));

	itemRefMesh = CreateDefaultSubobject<UStaticMeshComponent>("Attached Item reference");
	itemRefMesh->SetupAttachment(MouthAttachment);
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
	FindClosestPickup();
	if (itemRef)
	{
		if (FindClosestPickup() <= interactRange && FindClosestPickup() > 0)
		{
			itemRef->GetOutlineComponent()->bEnabled = true;
		}
		else
		{
			itemRef->GetOutlineComponent()->bEnabled = false;
		}

	}
	

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
			tempActor->OnHit();
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




	if (FindClosestPickup() <= interactRange && FindClosestPickup() > 0)
	{
		if (itemRef && !itemRef->GetPickedUp())
		{
			
			PickUpItem(itemRef);
		}
		else
		{

			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, FString::Printf(TEXT("NO ITEM")));
		}
	}


	else if (tempInteractible)
	{
		tempInteractible->Interact();
	}


}

void ACatBase::PickUpItem(APickupBase* pickupTemp)
{
	//when cat interacts with an object that can be picked up call this function
				
	 			GetAttachedActors(AttachedActors);
	 			if (AttachedActors.IsEmpty())
	 			{
					
					Parameters.AddIgnoredActor(pickupTemp);
					pickupTemp->PickUp(this);
					pickupTemp->GetOutlineComponent()->bEnabled=false;

	 			}
	 			else
	 			{
					Parameters.ClearIgnoredActors();
					Parameters.AddIgnoredActor(this);
					Parameters.AddIgnoredActor(pickupTemp);
					APickupBase* heldItem = Cast<APickupBase>(AttachedActors[0]);
	 				heldItem->Drop(this);

					pickupTemp->PickUp(this);
	 			}



}

float ACatBase::FindClosestPickup()
{

	class AActor* closestPickup = nullptr;
	AActor* MyOwner = GetOwner();
	TArray<AActor*> foundPickups;
	
	
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APickupBase::StaticClass(), foundPickups);
		int arraysize = foundPickups.Num();
		float currentClosestDistance = TNumericLimits<float>::Max();
		GEngine->AddOnScreenDebugMessage(-1, 0.01, FColor::Blue, FString::Printf(TEXT("array size: %i"), arraysize));


		for (int i = 0; i < foundPickups.Num(); i++)
		{
			
			APickupBase* tempPickup = Cast<APickupBase>(foundPickups[i]); 

			float distance = DistanceBetween(this,foundPickups[i]);

			GEngine->AddOnScreenDebugMessage(-1, 0.01, FColor::Blue, FString::Printf(TEXT("%f"), distance));
			if (distance < currentClosestDistance && tempPickup && !tempPickup->GetPickedUp())
			{

				currentClosestDistance = distance;
				closestPickup = foundPickups[i];
			
				itemRef = tempPickup;
				closestPickup = foundPickups[i];

			}
			
		}

		if (closestPickup)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.01, FColor::Cyan, FString::Printf(TEXT("closest %f"), currentClosestDistance));
			return currentClosestDistance;

		}
		return 0.f;
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

float ACatBase::DistanceBetween(AActor* A, AActor* B)
{
	return (A->GetActorLocation() - B->GetActorLocation()).Size();
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


