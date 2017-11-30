// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	//把Barrel旋转到正确的角度——这一帧
	//给一个最大旋转速度
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);

	auto RotationToChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationToChange;

	SetRelativeRotation(FRotator(0.f, NewRotation, 0.f));
}



