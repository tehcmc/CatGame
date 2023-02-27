// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
#include "PickupBase.h"




void APickupBase::PickUp(ACatBase* catRef)
{
	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::SnapToTarget, false);

	RootComponent->AttachToComponent(catRef->GetMouthAttachment(),rules, TEXT("Item Mesh"));

}

void APickupBase::OnPickup()
{
	//do something when item is picked up


}
