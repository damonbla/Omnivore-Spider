// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CableComponent.h"
#include "WebRopeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OMNIVORE_API UWebRopeComponent : public UActorComponent
{
	GENERATED_BODY()

	ACharacter* OwnerRef;
	
	TArray<UCableComponent*> WebRopes;

	class AWebAttachmentPoint* RopeAttachmentPoint;

	class USkeletalMeshComponent* SpiderSkeleton;

	void SetPositionOnRope();

	void DisengageFromWebRope();

	float PositionBetweenPoints;

	int CurrentPointUnderSpider;

	float WebRopeStartLength{ 10.0f };

	double ClimbStartSpeed;
	
public:	
	// Sets default values for this component's properties
	UWebRopeComponent();

	UPROPERTY(BlueprintReadOnly)
	bool bIsOnWebRope{ false };

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartWeb();

	UFUNCTION(BlueprintCallable)
	void DropFromWebRope();

	UFUNCTION(BlueprintCallable)
	void JumpFromWebRope(FVector Direction);

	UFUNCTION(BlueprintCallable)
	void ClimbWebRope(bool Down);

	UFUNCTION(BlueprintCallable)
	void SwingWebRope(FVector Direction);

	UPROPERTY(EditAnywhere)
	double ClimbSpeed{ 0.5 };

	UPROPERTY(EditAnywhere)
	float SwingForce{ 50.0 };

	UPROPERTY(EditAnywhere)
	float JumpMultiplier{ 100.0 };

	UPROPERTY(EditAnywhere)
	UMaterial* WebRopeMaterial;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
