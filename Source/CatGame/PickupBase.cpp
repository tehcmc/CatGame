// Fill out your copyright notice in the Description page of Project Settings.
#include "PickupBase.h"
#include "Components/SphereComponent.h"




void APickupBase::PickUp(ACatBase* catRef)
{
	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::SnapToTarget, false);
	this->DisableComponentsSimulatePhysics();//disable physics before attaching
	AttachToActor(catRef,rules);
	SetActorLocation(catRef->GetMouthAttachment()->GetComponentLocation());
	SetActorRotation(catRef->GetItemRefMesh()->GetComponentRotation());
	OnPickup();
}

void APickupBase::Drop(ACatBase* catRef)
{
	FDetachmentTransformRules rules(FDetachmentTransformRules::KeepWorldTransform);
	DetachFromActor(rules);
	OnDropped(); 
}

void APickupBase::OnDropped_Implementation()
{

}

void APickupBase::OnPickup_Implementation()
{

}

