// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "MoverComponent.h"
#include "TriggerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UTriggerComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* GetAcceptableActor() const;

	UFUNCTION(BlueprintCallable)
	void SetMoverComponent(UMoverComponent* NewMoverComponent);

	UPROPERTY(EditAnywhere)
	FName TriggerTagName;


	UMoverComponent* MoverComponent;
};
