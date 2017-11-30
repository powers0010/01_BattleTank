// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
class UTankTrack;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:		//
	
		UFUNCTION(BlueprintCallable , category = "Input")
		void MoveForward(float Throw);

		UFUNCTION(BlueprintCallable, category = "Input")
			void TurnRight(float Throw);

		UFUNCTION(BlueprintCallable, category = "Input")
			void Initalize(UTankTrack* TankTrackLeftlToSet, UTankTrack* TankTrackRightToSet);
		/** path following: request new velocity */

		virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

protected:
	UPROPERTY(BlueprintReadOnly, category = "component")
		UTankTrack* TankTrackLeft = nullptr;
	UPROPERTY(BlueprintReadOnly, category = "component")
		UTankTrack* TankTrackRight = nullptr;

};
