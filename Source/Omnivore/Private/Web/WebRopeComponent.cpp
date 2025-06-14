// Fill out your copyright notice in the Description page of Project Settings.


#include "Web/WebRopeComponent.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Web/WebAttachmentPoint.h>


// Sets default values for this component's properties
UWebRopeComponent::UWebRopeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	OwnerRef = GetOwner<ACharacter>();
}


// Called when the game starts
void UWebRopeComponent::BeginPlay()
{
	Super::BeginPlay();

	PhysicsBody = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();

	ClimbStartSpeed = ClimbSpeed;
}


// Called every frame
void UWebRopeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// get the location of the end of the last created rope
	if (bIsOnWebRope) {
		SetPositionOnRope();
	}
}


void UWebRopeComponent::StartWeb() {
	if (bIsOnWebRope) return;

	// create attachment point right here at spider's location
	FActorSpawnParameters SpawnParams;
	FVector SpawnLocation = OwnerRef->GetActorLocation();
	// Add a bit so it's not hanging in space but on the surface itself
	SpawnLocation.Z += 10.0;
	RopeAttachmentPoint = GetWorld()->SpawnActor<AWebAttachmentPoint>(AWebAttachmentPoint::StaticClass(), SpawnLocation, FRotator::ZeroRotator, SpawnParams);

	// create a new cablecomponent
	UCableComponent* WebRope = Cast<UCableComponent>(GetOwner()->AddComponentByClass(UCableComponent::StaticClass(), false, FTransform::Identity, true));

	// rope settings
	WebRope->CableLength = WebRopeStartLength;
	WebRope->NumSegments = 8;
	WebRope->SolverIterations = 4;
	WebRope->CableWidth = 0.5;
	WebRope->NumSides = 6;
	WebRope->bEnableCollision = false;
	WebRope->bAttachEnd = false;
	//WebRope->bUseSubstepping = true; // fixes flickering problem (bug, still present in unreal 5.5)
	//WebRope->SubstepTime = 0.01; // fixes flickering problem (bug, still present in unreal 5.5)
	//WebRope->SetTickGroup(TG_PostUpdateWork);

	WebRope->SetMaterial(0, WebRopeMaterial);

	WebRope->AttachToComponent(RopeAttachmentPoint->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);

	// finish it up, now those settings will be applied
	GetOwner()->FinishAddComponent(WebRope, false, FTransform::Identity);

	WebRopes.Add(WebRope);

	// we are starting out at the very last point of the rope
	CurrentPointUnderSpider = WebRope->NumSegments;
	PositionBetweenPoints = 0.5;
	
	bIsOnWebRope = true;
}


void UWebRopeComponent::SetPositionOnRope() {
	TArray<FVector> WebRopePoints;
	WebRopes.Last()->GetCableParticleLocations(WebRopePoints);

	if (WebRopePoints.Num() >= 2 && CurrentPointUnderSpider > 0 && CurrentPointUnderSpider <= WebRopes.Last()->NumSegments) {
		// Point under spider and the one above it (we are between these two points)
		FVector PointUnder{ WebRopePoints[CurrentPointUnderSpider] };
		FVector PointOver{ WebRopePoints[CurrentPointUnderSpider - 1] };

		FVector PositionOnRope = FMath::Lerp(PointUnder, PointOver, PositionBetweenPoints);

		OwnerRef->SetActorLocation(PositionOnRope);
	}
}

void UWebRopeComponent::DisengageFromWebRope() {
	if (!bIsOnWebRope) return;

	bIsOnWebRope = false;

	ClimbSpeed = ClimbStartSpeed;
}


void UWebRopeComponent::DropFromWebRope() {
	DisengageFromWebRope();

	OwnerRef->GetCharacterMovement()->Velocity = FVector::ZeroVector;
}


void UWebRopeComponent::JumpFromWebRope(FVector Direction) {
	DisengageFromWebRope();

	FVector LaunchVector = (Direction * JumpMultiplier) + FVector(0.0, 0.0, 500.0);

	OwnerRef->LaunchCharacter(LaunchVector, true, true);
}


void UWebRopeComponent::ClimbWebRope(bool Down) {
	//UE_LOG(LogTemp, Warning, TEXT("PositionBetweenPoints: %s"), *FString::SanitizeFloat(PositionBetweenPoints));
	//UE_LOG(LogTemp, Warning, TEXT("CurrentPointUnderSpider: %s"), *FString::FromInt(CurrentPointUnderSpider));

	if (Down) {
		PositionBetweenPoints -= ClimbSpeed;
		if (PositionBetweenPoints <= 0.0) {
			if (CurrentPointUnderSpider == WebRopes.Last()->NumSegments) {
				// we are at the very bottom of the web rope
				PositionBetweenPoints = 0.0;

				WebRopes.Last()->CableLength += 0.75;
				float ratio = WebRopeStartLength / WebRopes.Last()->CableLength;
				ClimbSpeed = ClimbStartSpeed * ratio;
				return;
			}

			PositionBetweenPoints = 1.0;
			CurrentPointUnderSpider++;
		}
		return;
	}


	PositionBetweenPoints += ClimbSpeed;
	if (PositionBetweenPoints >= 1.0) {
		if (CurrentPointUnderSpider == 1) {
			// we are at the very top of the web rope
			PositionBetweenPoints = 1.0;

			// ... get back on the surface

			UE_LOG(LogTemp, Warning, TEXT("Top"));
			return;
		}

		PositionBetweenPoints = 0.0;
		CurrentPointUnderSpider--;
	}
}


void UWebRopeComponent::SwingWebRope(FVector Direction) {
	TArray<FVector> ParticleLocations;
	WebRopes.Last()->GetCableParticleLocations(ParticleLocations);

	if (ParticleLocations.Num() > 0) {
		int32 TargetIndex = ParticleLocations.Num() - 1;
		FVector ForceDirection = Direction * SwingForce;

		WebRopes.Last()->CableForce = ForceDirection;
	}

}
