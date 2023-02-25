// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnpointBase.h"
//	spawn point base
//  attach to furniture blueprints to allow for randomized spawns
//	also used as a score incrementer, object leaves spawn bounds, increment score
// 
// Sets default values
ASpawnpointBase::ASpawnpointBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnpointBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnpointBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

