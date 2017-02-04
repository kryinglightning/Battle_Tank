// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankAimComponent.h"
#include "TankBarrel.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimComponent) { return; }
	TankAimComponent->AimAt(HitLocation, LaunchSpeed);

}

void ATank::Fire()
{
	bool isReloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTimeSec; 
	if (Barrel && isReloaded) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBP,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
	return;
}