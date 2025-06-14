// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SpiderWalkComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "Engine/Engine.h"
#include "Logging/LogMacros.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
USpiderWalkComponent::USpiderWalkComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USpiderWalkComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerRef = GetOwner<ACharacter>();
	Controller = GetWorld()->GetFirstPlayerController();
	MovementComp = OwnerRef->GetCharacterMovement();
	SkeletalComp = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	
	TargetGravity = NewGravity = FVector::DownVector;
}

// Called every frame
void USpiderWalkComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// this will stop the problem of continuously trying to check and change the gravity while
	// it is already in the process of changing (causing jumpiness)
	if (TargetGravity != NewGravity) {
		ChangeGravity(NewGravity, DeltaTime);
		return;
	}

	FHitResult HitResult;
	FVector SpiderLocation{ OwnerRef->GetActorLocation() };

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerRef);
	Params.bTraceComplex = true;

	// step 1: is there a wall in front of us?
	FVector Forward{ SpiderLocation + OwnerRef->GetActorForwardVector() * 20.0f };

	if (GetWorld()->LineTraceSingleByChannel(HitResult, SpiderLocation, Forward, ECC_GameTraceChannel1, Params)) {
		FVector SurfaceNormal = HitResult.ImpactNormal * -1;
		NewGravity = SurfaceNormal;

		TargetGravity = FMath::VInterpTo(TargetGravity, SurfaceNormal, DeltaTime, 20.0);

		if (bDebugMode) {
			UKismetSystemLibrary::DrawDebugArrow(
				GetWorld(),
				SpiderLocation,
				Forward,
				1.0,
				FLinearColor::Yellow,
				0.1,
				0.5
			);
		}

		return;
	}


	// step 2: if we are falling (having jumped for example), down is always DOWN (spiders always land on their feet!)
	if (OwnerRef->GetCharacterMovement()->IsFalling()) {
		NewGravity = FVector::DownVector;
		ChangeGravity(NewGravity, DeltaTime);

		return;
	}


	// step 3: just checking down at the current walking surface a certain distance
	FVector Down{ SpiderLocation - OwnerRef->GetActorUpVector() * 20.0 };

	if (GetWorld()->LineTraceSingleByChannel(HitResult, SpiderLocation, Down, ECC_GameTraceChannel1, Params)) {
		FVector SurfaceNormal = HitResult.ImpactNormal * -1;
		NewGravity = SurfaceNormal;

		ChangeGravity(SurfaceNormal, DeltaTime);

		if (bDebugMode) {
			UKismetSystemLibrary::DrawDebugArrow(
				GetWorld(),
				SpiderLocation,
				Down,
				1.0,
				FLinearColor::Blue,
				0.1,
				0.5
			);
		}

		return;
	}


	// step 4: we hit nothing and aren't falling, we must be coming over an edge
	FVector DownAndBack{ Down + OwnerRef->GetActorForwardVector() * -10 };
	FVector DownAndBackStart{ SpiderLocation + OwnerRef->GetActorForwardVector() * 10 };

	if (GetWorld()->LineTraceSingleByChannel(HitResult, DownAndBackStart, DownAndBack, ECC_GameTraceChannel1, Params)) {
		FVector SurfaceNormal = HitResult.ImpactNormal * -1;
		NewGravity = SurfaceNormal;

		ChangeGravity(SurfaceNormal, DeltaTime);

		if (bDebugMode) {
			UKismetSystemLibrary::DrawDebugArrow(
				GetWorld(),
				DownAndBackStart,
				DownAndBack,
				1.0,
				FLinearColor::Green,
				0.1,
				0.5
			);
		}

		return;
	}




	//UE_LOG(LogTemp, Warning, TEXT("TargetGravity %s"), *TargetGravity.ToString());
}



void USpiderWalkComponent::ChangeGravity(FVector ToGravity, float DeltaTime) {
	TargetGravity = FMath::VInterpTo(TargetGravity, ToGravity, DeltaTime, 20.0);
}

