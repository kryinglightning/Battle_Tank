// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimComponent.h" //needs to be the last



// Sets default values for this component's properties
UTankAimComponent::UTankAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimComponent::BeginPlay() {
	LastFireTime = FPlatformTime::Seconds(); //so that 1st fire is after initial reload
}

void UTankAimComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;

}

void UTankAimComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	if (RoundsLeft <= 0) {
		FiringState = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeSec) {
		FiringState = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringState = EFiringStatus::Aiming;
	}
	else {
		FiringState = EFiringStatus::Ready;
	}

}

EFiringStatus UTankAimComponent::GetFiringStatus() const {
	return EFiringStatus();
}

int UTankAimComponent::GetRoundsLeft() const {
	return RoundsLeft;
}

bool UTankAimComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}

void UTankAimComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName ("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	};
}

void UTankAimComponent::MoveBarrel(FVector AimDirection) {
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	if (DeltaRotator.Yaw < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else {
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

void UTankAimComponent::Fire() {
	if (FiringState != EFiringStatus::Aiming || FiringState != EFiringStatus::Ready) {
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBP)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBP,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}
	return;
}



