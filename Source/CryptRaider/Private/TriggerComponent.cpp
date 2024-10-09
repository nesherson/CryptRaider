// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	const AActor* AcceptableActor = GetAcceptableActor();
	
	if (AcceptableActor != nullptr)
	{
		MoverComponent->SetShouldMove(true);
	}
	else
	{
		MoverComponent->SetShouldMove(false);
	}
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> OverlappingActors;

	GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor->ActorHasTag(TriggerTagName))
			return Actor;
	}

	return nullptr;
}

void UTriggerComponent::SetMoverComponent(UMoverComponent* NewMoverComponent)
{
	MoverComponent = NewMoverComponent;
}
