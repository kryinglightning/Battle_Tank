// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be the last include

/**
 * 
 */

UCLASS()
class BATTLE_TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	ATank* GetControlledTank() const;

private:
	void AimAtCrosshair(); //move the barrel to the crosshair to shoot in that direction
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	
	
};
