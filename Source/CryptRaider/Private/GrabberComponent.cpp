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
}

// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();

	const UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	bool IsNull = PhysicsHandle == nullptr;
	FString StrNull = FString(IsNull ? "Null" : "Not null");

	UE_LOG(LogTemp, Display, TEXT("Physics handler -> %s"), *StrNull)
	
	if (PhysicsHandle == nullptr)
		return;

	UE_LOG(LogTemp, Display, TEXT("Physics handler -> %s"), *PhysicsHandle->GetName());
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UGrabberComponent::Grab()
{
	UE_LOG(LogTemp, Display, TEXT("Grab"));
	// DrawDebugLine(World, Start, End, FColor::Red);
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
		const AActor* HitActor = HitResult.GetActor();
		// UE_LOG(LogTemp, Display, TEXT("Time -> %f,Actor hit -> %s"), World->TimeSeconds, *HitActor->GetName());
		DrawDebugSphere(World, HitResult.Location, 10, 10, FColor::Yellow, false, 5);
		DrawDebugSphere(World, HitResult.ImpactPoint, 10, 10, FColor::Green, false, 5);
	}
}

void UGrabberComponent::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Release"));
}


	