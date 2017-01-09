// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSec * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	SetRelativeRotation(FRotator(FMath::Clamp(RawNewElevation, MinElevation, MaxElevation), 0, 0));
}


