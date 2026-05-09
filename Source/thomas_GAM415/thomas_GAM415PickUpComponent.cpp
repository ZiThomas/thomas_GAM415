// Copyright Epic Games, Inc. All Rights Reserved.

#include "thomas_GAM415PickUpComponent.h"

Uthomas_GAM415PickUpComponent::Uthomas_GAM415PickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void Uthomas_GAM415PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &Uthomas_GAM415PickUpComponent::OnSphereBeginOverlap);
}

void Uthomas_GAM415PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	Athomas_GAM415Character* Character = Cast<Athomas_GAM415Character>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
