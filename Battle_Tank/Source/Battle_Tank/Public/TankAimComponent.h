// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimComponent.generated.h"

//enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
	Reloading, 
	Aiming,
	Ready
};

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void AimAt(FVector HitLocation, float LaunchSpeed);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringState = EFiringStatus::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimComponent();

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	void MoveBarrel(FVector AimDirection);

};
