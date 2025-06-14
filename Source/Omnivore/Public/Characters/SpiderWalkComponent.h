// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpiderWalkComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OMNIVORE_API USpiderWalkComponent : public UActorComponent
{
	GENERATED_BODY()

	void ChangeGravity(FVector ToGravity, float DeltaTime);

	ACharacter* OwnerRef;
	APlayerController* Controller;
	class UCharacterMovementComponent* MovementComp;
	class USkeletalMeshComponent* SkeletalComp;

	UPROPERTY(EditAnywhere)
	FName FrontLeftLeg;

	UPROPERTY(EditAnywhere)
	bool bDebugMode{ false };

	FVector NewGravity;

public:	
	// Sets default values for this component's properties
	USpiderWalkComponent();

	UPROPERTY(BlueprintReadOnly)
	FVector TargetGravity;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
