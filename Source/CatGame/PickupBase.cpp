// Fill out your copyright notice in the Description page of Project Settings.
#include "PickupBase.h"
#include "components/StaticMeshComponent.h"
#include "Components/PostProcessComponent.h"
#include "CatBase.h"
#include "Components/SphereComponent.h"


APickupBase::APickupBase()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

	OutlineComponent = CreateDefaultSubobject<UPostProcessComponent>("Outline Component");
	OutlineComponent->SetupAttachment(MeshComponent);
}

void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	OutlineComponent->SetActive(false);
}

void APickupBase::PickUp(ACatBase* catRef)
{
	//										location						rotation					scale				     weld
	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld,    true  );
	SetActorRotation(catRef->GetItemRefMesh()->GetComponentRotation());

	this->DisableComponentsSimulatePhysics();//disable physics before attaching
	AttachToComponent(catRef->GetItemRefMesh(),rules);
		//SetActorLocation(catRef->GetMouthAttachment()->GetComponentLocation());

	SetPickedUp(true);
	OnPickup();
}

void APickupBase::Drop(ACatBase* catRef)
{
	FDetachmentTransformRules rules(FDetachmentTransformRules::KeepWorldTransform);
	DetachFromActor(rules);
	SetActorEnableCollision(true);
	SetPickedUp(false);
	OnDropped(); 
}

void APickupBase::OnDropped_Implementation()
{

}

void APickupBase::OnPickup_Implementation()
{

}

