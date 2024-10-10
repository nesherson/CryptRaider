#include "TriggerComponent.h"
#include "GameFramework/Actor.h"

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

	if (AActor* AcceptableActor = GetAcceptableActor())
	{
		if (UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(AcceptableActor->GetRootComponent()))
			Component->SetSimulatePhysics(false);
		
		AcceptableActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
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
		if (Actor->ActorHasTag(TriggerTagName) && !Actor->ActorHasTag("Grabbed"))
			return Actor;
	}

	return nullptr;
}

void UTriggerComponent::SetMoverComponent(UMoverComponent* NewMoverComponent)
{
	MoverComponent = NewMoverComponent;
}
