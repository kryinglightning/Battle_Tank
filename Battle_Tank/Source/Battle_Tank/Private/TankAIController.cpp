// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	auto ControlledTank = Cast<ATank>(GetPawn());
	
	if (PlayerTank)
	{
		// TODO Move towards the player

		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//fire at the player
		ControlledTank->Fire(); //TODO limit fire rate
	}
}

