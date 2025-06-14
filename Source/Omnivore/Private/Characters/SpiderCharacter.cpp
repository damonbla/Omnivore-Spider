// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SpiderCharacter.h"

// Sets default values
ASpiderCharacter::ASpiderCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpiderCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpiderCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpiderCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

