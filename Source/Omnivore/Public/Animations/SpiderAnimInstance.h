// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SpiderAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class OMNIVORE_API USpiderAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentSpeed{ 0.0f };

	UFUNCTION(BlueprintCallable)
	void UpdateSpeed();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentDirection{ 0.0f };

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector LegLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Velocity;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateDirection();

	UFUNCTION(BlueprintCallable)
	void MoveLeg();
};
