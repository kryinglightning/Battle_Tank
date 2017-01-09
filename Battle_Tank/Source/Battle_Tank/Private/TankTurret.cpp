// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * MaxRotationSpeed * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator (0, RawNewRotation, 0));
}



