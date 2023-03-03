// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreBounds.h"


#include "ItemBase.h"


// Sets default values
AScoreBounds::AScoreBounds()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ScoreBox = CreateDefaultSubobject<UBoxComponent>("Score Bounds");
	ScoreBox->SetupAttachment(RootComponent);
	ScoreBox->OnComponentBeginOverlap.AddDynamic(this,&AScoreBounds::OnOverlap);
}

// Called when the game starts or when spawned
void AScoreBounds::BeginPlay()
{
	Super::BeginPlay();
	
}


void AScoreBounds::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AItemBase* tempItem = Cast<AItemBase>(OtherActor);
	if (tempItem)
	{
		tempItem->HitScoreBounds();
	}

}

// Called every frame
void AScoreBounds::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

