#include "GrabberComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

UGrabberComponent::UGrabberComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	MaxGrabDistance = 400;
	GrabRadius = 100;
	HoldDistance = 200;
}

void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle == nullptr)
		return;

	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		const FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabberComponent::Grab() const
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle == nullptr)
		return;

	if (FHitResult HitResult; GetGrabbableInReach(HitResult))
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 10);
		AActor* HitActor = HitResult.GetActor();
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		
		HitActor->Tags.Add("Grabbed");
		HitComponent->WakeAllRigidBodies();
		HitComponent->SetSimulatePhysics(true);
		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent,
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
	
	UPrimitiveComponent* GrabbedComponent = PhysicsHandle->GetGrabbedComponent();
	
	if (GrabbedComponent == nullptr)
		return;

	GrabbedComponent->WakeAllRigidBodies();
	GrabbedComponent->GetOwner()->Tags.Remove("Grabbed");
	PhysicsHandle->ReleaseComponent();
}

UPhysicsHandleComponent* UGrabberComponent::GetPhysicsHandle() const
{
	if (UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>())
		return PhysicsHandle;
	
	UE_LOG(LogTemp, Warning, TEXT("GrabberComponent::GetPhysicsHandle: Can't find physics handle!"));
	return nullptr;
}

bool UGrabberComponent::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	const UWorld* World =  GetWorld();
	const FVector Start = GetComponentLocation();
	const FVector End = Start + GetForwardVector() * MaxGrabDistance;
	
	return World->SweepSingleByChannel(
		OutHitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(GrabRadius));
}


	