// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SpiderCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class OMNIVORE_API USpiderCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	void UpdateBasedMovement(float DeltaSeconds) override;

	float SlideAlongSurface(const FVector& Delta, float Time, const FVector& InNormal, FHitResult& Hit, bool bHandleImpact) override;

	void FindFloor(const FVector& CapsuleLocation, FFindFloorResult& OutFloorResult, bool bCanUseCachedLocation, const FHitResult* DownwardSweepResult) const override;
};
