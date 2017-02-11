// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankAIController.h"
#include "TankAimComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	auto ControlledTank = GetPawn();
	
	if (!ensure(PlayerTank && ControlledTank)) { return; }
	MoveToActor(PlayerTank, 300.0f);

	// Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//TODO fix fire at the player
	AimingComponent->Fire(); //TODO limit fire rate
}

