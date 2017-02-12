// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankAimComponent.h"
#include "TankPlayerController.h"


#define OUT

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto AimComponent = GetPawn()->FindComponentByClass<UTankAimComponent>();
	if (!ensure(AimComponent)) { return; }
	FoundAimingComponent(AimComponent);

}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AimAtCrosshair();
}


void ATankPlayerController::AimAtCrosshair() {
	if (!GetPawn()) { return;  }
	auto AimComponent = GetPawn()->FindComponentByClass<UTankAimComponent>();
	if (!ensure(AimComponent)) { return; }

	FVector HitLocation; //OUT parameter
	if (GetSightRayHitLocation(HitLocation)) {
		AimComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	///find the crosshair position
	int32 ViewportSizeX;
	int32 ViewportSizeY; 
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D (CrosshairXLocation*ViewportSizeX, CrosshairYLocation*ViewportSizeY);

	///de-project screen position to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//line trace along LookDirection, see what we hit up to mx range
		GetLookVectorHitLocation(LookDirection, HitLocation);
	};
	 return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld
	(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	FVector CameraPosition = PlayerCameraManager->GetCameraLocation();
	FVector End = CameraPosition + (LookDirection * MaxRange);
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			CameraPosition,
			End,
			ECollisionChannel::ECC_Visibility)
		) {
		HitLocation = HitResult.Location;
		return true;
	}
	else {
		HitLocation = FVector(0);
		return false;
	}
}


