// Fill out your copyright notice in the Description page of Project Settings.

#include "MoverComponent.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMoverComponent::UMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MoveTime = 4;
	ShouldMove = false;
	// ...
}

// Called when the game starts
void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();	
}

// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove)
	{
		UE_LOG(LogTemp, Warning, TEXT("UMoverComponent::TickComponent"));
		MoveActor(DeltaTime);
	}
}

void UMoverComponent::SetShouldMove(const bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}

void UMoverComponent::MoveActor(const float DeltaTime) const
{
	AActor* Owner = GetOwner();
	const FVector CurrentLocation = Owner->GetActorLocation();
	const FVector TargetLocation = OriginalLocation + MoveOffset;
	const float Speed = FVector::Dist(CurrentLocation, TargetLocation) / MoveTime;
	const FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

	Owner->SetActorLocation(NewLocation);
}




