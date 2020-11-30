#pragma once

#include "CoreMinimal.h"

class AActor;
class USceneComponent;

struct FFGFrameMovement 
{
	FFGFrameMovement(const FVector& InstartLocation) : 
		StartLocation(InstartLocation) {}

	FFGFrameMovement(AActor* InActor);
	FFGFrameMovement(USceneComponent* InSceneComponent);

	void AddDelta(const FVector& InDelta);

	FVector GetMovementDelta() const { return MovementDelta; }

	FHitResult Hit;

	FVector FinalLocation = FVector::ZeroVector;

private:
	FVector MovementDelta = FVector::ZeroVector;
	FVector StartLocation = FVector::ZeroVector;
};