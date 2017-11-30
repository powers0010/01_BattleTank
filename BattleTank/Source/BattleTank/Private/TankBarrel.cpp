// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	//把Barrel旋转到正确的角度——这一帧
	//给一个最大旋转速度
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);

	float EevateToChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	float NewElevation = RelativeRotation.Pitch + EevateToChange;
//	UE_LOG(LogTemp, Warning, TEXT("NewElevation %f"), NewElevation);
	
	auto Elevation = FMath::Clamp<float>(NewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0.f, 0.f));
}

