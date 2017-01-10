// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankAimComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect points as added at construction
	TankAimComponent = CreateDefaultSubobject<UTankAimComponent>(FName("Aiming Component"));
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	TankAimComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) {
	if (!TurretToSet) { return; }
	TankAimComponent->SetTurretReference(TurretToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimComponent->AimAt(HitLocation, LaunchSpeed);

}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Firing"));
	return;
}