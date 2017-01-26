// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Tank.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call Super as we're replacing the functionality
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForward = MoveVelocity.GetSafeNormal();

	float ForwardDirection = FVector::DotProduct(TankForward, AIForward);
	IntendMoveForward(ForwardDirection);

	float RotationDirection = FVector::CrossProduct(TankForward, AIForward).Z;
	IntendTurnRight(RotationDirection);

}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}




