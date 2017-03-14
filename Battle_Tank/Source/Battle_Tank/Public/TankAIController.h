// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAimComponent.h"
#include "TankAIController.generated.h"

/**
 * 
 */

UCLASS()
class BATTLE_TANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 80000.0f;

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
