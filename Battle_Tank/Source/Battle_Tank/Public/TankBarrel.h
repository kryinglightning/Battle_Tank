// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLE_TANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	//-1 is max downward movement, +1 - max upward movement
	void Elevate (float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSec = 20;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation = 32;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevation = 0;
	
};