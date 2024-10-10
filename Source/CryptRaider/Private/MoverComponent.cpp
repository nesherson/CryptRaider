
#include "MoverComponent.h"
#include "Math/UnrealMathUtility.h"

UMoverComponent::UMoverComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	MoveTime = 4;
	ShouldMove = false;
}

void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
}

void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Owner = GetOwner();
	const FVector CurrentLocation = Owner->GetActorLocation();
	FVector TargetLocation = OriginalLocation;
	
	if (ShouldMove)
		TargetLocation = OriginalLocation + MoveOffset;
	
	const float Speed = MoveOffset.Length() / MoveTime;
	const FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	
	Owner->SetActorLocation(NewLocation);
}

void UMoverComponent::SetShouldMove(const bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}

void UMoverComponent::MoveActor(const float DeltaTime, const bool ReverseMovement) const
{
	AActor* Owner = GetOwner();
	const FVector CurrentLocation = Owner->GetActorLocation();
	const FVector TargetLocation = ReverseMovement ? OriginalLocation : OriginalLocation + MoveOffset;
	const float Speed = MoveOffset.Length() / MoveTime;
	const FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	
	Owner->SetActorLocation(NewLocation);
}




