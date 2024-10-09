// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "GrabberComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabberComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabberComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void Grab() const;
	
	UFUNCTION(BlueprintCallable)
	void Release() const;

	
	UPROPERTY(EditAnywhere)
	float MaxGrabDistance;

	UPROPERTY(EditAnywhere)
	float HoldDistance;

	UPROPERTY(EditAnywhere)
	float GrabRadius;
private:
	
	UPhysicsHandleComponent* GetPhysicsHandle() const;
};
