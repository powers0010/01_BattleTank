// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	//��Barrel��ת����ȷ�ĽǶȡ�����һ֡
	//��һ�������ת�ٶ�
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);

	float EevateToChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	float NewElevation = RelativeRotation.Pitch + EevateToChange;
//	UE_LOG(LogTemp, Warning, TEXT("NewElevation %f"), NewElevation);
	
	auto Elevation = FMath::Clamp<float>(NewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0.f, 0.f));
}

