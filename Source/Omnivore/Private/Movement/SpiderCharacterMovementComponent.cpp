// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement/SpiderCharacterMovementComponent.h"
#include "Logging/LogMacros.h"

void USpiderCharacterMovementComponent::UpdateBasedMovement(float DeltaSeconds)
{
	Super::UpdateBasedMovement(DeltaSeconds);

	//UE_LOG(LogTemp, Warning, TEXT("UpdateBasedMovement %s"), *FString::SanitizeFloat(DeltaSeconds));
}

float USpiderCharacterMovementComponent::SlideAlongSurface(const FVector& Delta, float Time, const FVector& InNormal, FHitResult& Hit, bool bHandleImpact)
{
	Super::SlideAlongSurface(Delta, Time, InNormal, Hit, bHandleImpact);

	//UE_LOG(LogTemp, Warning, TEXT("SlideAlongSurface"));

	return 0.0f;
}

void USpiderCharacterMovementComponent::FindFloor(const FVector& CapsuleLocation, FFindFloorResult& OutFloorResult, bool bCanUseCachedLocation, const FHitResult* DownwardSweepResult) const
{
	Super::FindFloor(CapsuleLocation, OutFloorResult, bCanUseCachedLocation, DownwardSweepResult);

	//UE_LOG(LogTemp, Warning, TEXT("FindFloor"));
}
