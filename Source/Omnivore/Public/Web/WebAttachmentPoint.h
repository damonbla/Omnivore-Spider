// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WebAttachmentPoint.generated.h"

UCLASS()
class OMNIVORE_API AWebAttachmentPoint : public AActor
{
	GENERATED_BODY()

	class USceneComponent* RootComponent;

public:	
	// Sets default values for this actor's properties
	AWebAttachmentPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
