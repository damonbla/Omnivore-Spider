// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/SpiderAnimInstance.h"


void USpiderAnimInstance::UpdateSpeed()
{
	APawn* PawnRef{ TryGetPawnOwner() };

	if (!IsValid(PawnRef)) { return; }

	FVector Velo{ PawnRef->GetVelocity() };

	CurrentSpeed = static_cast<float>(Velo.Length());

	// Check on this, it never gets changed here but it must in a blueprint somewhere
	// because if taken out animations stop working
	Velocity = FVector{ 0.0, 0.0, 0.0 };
}

void USpiderAnimInstance::UpdateDirection()
{
	APawn* PawnRef{ TryGetPawnOwner() };

	if (!IsValid(PawnRef)) { return; }

	CurrentDirection = CalculateDirection(
		PawnRef->GetVelocity(),
		PawnRef->GetActorRotation()
	);
}

void USpiderAnimInstance::MoveLeg()
{
	APawn* PawnRef{ TryGetPawnOwner() };

	if (!IsValid(PawnRef)) { return; }

	//LegLocation = PawnRef->GetActorLocation();
	//LegLocation.X += 5.0;
}
