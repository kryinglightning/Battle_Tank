// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "../Public/TankAIController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));
	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("The %s is the AI-controlled tank"), *(ControlledTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("The AI controlled tank is missing"));
	}
	
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("The %s is the AI-controlled tank"), *(PlayerTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Player Tank not found"));
	}
}


ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const {
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Error, TEXT("Player Tank not found"));
		return nullptr;
	}
	return Cast<ATank>(PlayerTank);
}


