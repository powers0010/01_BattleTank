// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	//��Barrel��ת����ȷ�ĽǶȡ�����һ֡
	//��һ�������ת�ٶ�
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);

	auto RotationToChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationToChange;

	SetRelativeRotation(FRotator(0.f, NewRotation, 0.f));
}



