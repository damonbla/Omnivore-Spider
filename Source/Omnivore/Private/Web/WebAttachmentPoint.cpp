// Fill out your copyright notice in the Description page of Project Settings.


#include "Web/WebAttachmentPoint.h"

// Sets default values
AWebAttachmentPoint::AWebAttachmentPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and set the root component so we can get a transform
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComponent);
}

// Called when the game starts or when spawned
void AWebAttachmentPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWebAttachmentPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

