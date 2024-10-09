// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "GrabberComponent.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MaxGrabDistance = 400;
	GrabRadius = 100;
	HoldDistance = 200;
}

// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle == nullptr)
		return;

	const FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
	
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
}

void UGrabberComponent::Grab() const
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle == nullptr)
		return;
	
	const UWorld* World =  GetWorld();
	const FVector Start = GetComponentLocation();
	const FVector End = Start + GetForwardVector() * MaxGrabDistance;
	
	FHitResult HitResult;
	const bool HasHit = World->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(GrabRadius));
	
	if (HasHit)
	{
		DrawDebugSphere(World, HitResult.ImpactPoint, 10, 10, FColor::Red, false, 10);
		PhysicsHandle->GrabComponentAtLocationWithRotation(HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation());
	}
}

void UGrabberComponent::Release() const
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle == nullptr)
		return;
	
	PhysicsHandle->ReleaseComponent();
}

UPhysicsHandleComponent* UGrabberComponent::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
	if ( PhysicsHandle != nullptr)
	{
		return PhysicsHandle;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("GrabberComponent::GetPhysicsHandle: Can't find physics handle!"));
	return nullptr;
}


	