// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBase.h"
//twastawtawtawrwsdawsdas
// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	MeshComponent->SetupAttachment(RootComponent);


	
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::OnHit_Implementation()
{

}

void AItemBase::OnScored_Implementation()
{

}

void AItemBase::HitScoreBounds()
{
	if (!HasScored)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("SCORE UP!!!!!!!!!!!!!!!!!")));
		HasScored = true;
		OnScored();
	}

}

