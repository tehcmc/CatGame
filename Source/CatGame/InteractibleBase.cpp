// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractibleBase.h"

// Sets default values
AInteractibleBase::AInteractibleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractibleBase::BeginPlay()
{
	Super::BeginPlay();
	
}



void AInteractibleBase::OnInteract_Implementation()
{
	
}

void AInteractibleBase::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Do something man")));
	OnInteract();
}


// Called every frame
void AInteractibleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

