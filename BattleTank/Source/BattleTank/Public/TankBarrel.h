// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom) , meta = (BlueprintSpawnableComponent))// , hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
		
	//
	void Elevate(float RelativeSpeed);

private:
	//转速
	UPROPERTY(EditAnywhere)
		float MaxDegreePerSecond = 5.f;
	//极限转角
	UPROPERTY(EditAnywhere)
		float MaxElevationDegrees = 40.f;
	UPROPERTY(EditAnywhere)
		float MinElevationDegrees = 0.f;

};
