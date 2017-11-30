// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::MoveForward(float Throw)
{
	if (!TankTrackLeft || !TankTrackRight)
	{
		return;
	}

	TankTrackLeft->SetThrottle(Throw);
	TankTrackRight->SetThrottle(Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//不需要 Super，重写
	//	Super::RequestDirectMove(MoveVelocity, bForceMaxSpeed);
	FVector velocity = MoveVelocity.GetSafeNormal();
//	FVector TankForwardDir = -1.f*GetOwner()->GetActorRightVector().GetSafeNormal();
	FVector TankForwardDir = GetOwner()->GetActorForwardVector().GetSafeNormal();

	MoveForward(10.f*FVector::DotProduct(TankForwardDir, velocity));

	TurnRight(10.f*FVector::CrossProduct(TankForwardDir, velocity).Z);

	//	FString Name = GetOwner()->GetName();
//	UE_LOG(LogTemp, Warning, TEXT("velocity %s"), *velocity.ToString());
	//	UE_LOG(LogTemp, Warning, TEXT("TankForwardDir %s"), *TankForwardDir.ToString());
	//	UE_LOG(LogTemp, Warning, TEXT("%f"), FVector::DotProduct(TankForwardDir, velocity));


}

void UTankMovementComponent::TurnRight(float Throw)
{
	if (!TankTrackLeft || !TankTrackRight)
	{
		return;
	}

	TankTrackLeft->SetThrottle(-1.f*Throw);
	TankTrackRight->SetThrottle(Throw);
}

void UTankMovementComponent::Initalize(UTankTrack* TankTrackLeftlToSet, UTankTrack* TankTrackRightToSet)
{
	if (!TankTrackLeftlToSet || !TankTrackRightToSet)
	{
		return;
	}
	TankTrackLeft = TankTrackLeftlToSet;
	TankTrackRight = TankTrackRightToSet;
}

