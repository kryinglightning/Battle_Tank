// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankAimComponent;
class UTankMovementComponent;

UCLASS()
class BATTLE_TANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimComponent* TankAimComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBP;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 1000.0f; 

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeSec = 3.0f;

	UTankBarrel* Barrel = nullptr; //TODO remove

	double LastFireTime = 0; 

};
