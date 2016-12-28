// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankPlayerController.h"

#define OUT

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
	auto ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("The %s is the pawn"), *(ControlledTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("The pawn is missing"));
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AimAtCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair() {
	if (!GetControlledTank()) {
		return;
	}

	FVector HitLocation; //OUT parameter
	if (GetSightRayHitLocation(HitLocation)) { //is going to raytrace
		UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *HitLocation.ToString());
		//tell the cotrolled tank to aim at this point
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	 HitLocation = FVector (1.0);
	 return true;
}


