// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimComponent::UTankAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
// Called every frame
void UTankAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (FPlatformTime::Seconds()- LastFireTime < ReloadFireTime)
	{
		AimState = EFiringState::ReLoading;
	}
	else if (IsBarrelMoving())
	{
		AimState = EFiringState::Aiming;
	}
	else
	{
		AimState = EFiringState::Locked;
	}
	// ...
}


bool UTankAimComponent::IsBarrelMoving()
{
	if (!BarrelComponent)
	{
		return true;
	}
//	FVector BarrelForward = -1.f* BarrelComponent->GetRightVector();
	FVector BarrelForward = BarrelComponent->GetForwardVector();
	return !BarrelForward.Equals(AimDirection ,0.02f);
}

void UTankAimComponent::Initalize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (BarrelToSet&&TurretToSet)
	{
		BarrelComponent = BarrelToSet;
		TurretComponent = TurretToSet;
	}
}

void UTankAimComponent::AimAt(FVector HitLocation)
{
	if (!BarrelComponent){	return;	}	
	if (!TurretComponent){	return;	}
	FVector TossVelocity;
	FVector StartLocation = BarrelComponent->GetSocketLocation(FName("Projectile"));//GetComponentLocation();//GetSocketLocation(FName("Projectile"));
//	UE_LOG(LogTemp, Warning, TEXT("StartLocation is %s"), *StartLocation.ToString());

	//���㷢�䷽��
	//������StartPos�ϵ�һ������ķ����ٶȣ������ն�����½��
	//������һ���еȵĻ�(�����ڵ����ϵ�45��)�������ٶ��ǿɱ�ģ�����Լ���ġ�û�и��١�
	// 	//UGameplayStatics::SuggestProjectileVelocity
	bool HaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		TossVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
//	UE_LOG(LogTemp, Warning, TEXT("TossVelocity is %s"), *TossVelocity.ToString());
	if (HaveAimSolution)
	{
		AimDirection = TossVelocity.GetSafeNormal();

//		UE_LOG(LogTemp, Warning, TEXT("AimDirection is %s"), *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
	}	
	else
	{
//		UE_LOG(LogTemp, Warning, TEXT("Have No Aim Solution"));
	}
}

void UTankAimComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!BarrelComponent || !TurretComponent)
	{
		return;
	}
	//��ǰBarrel��Rotator��AimDirection�Ĺ�ϵ
	FRotator BarrelRotator = BarrelComponent->GetForwardVector().Rotation();
//	FRotator BarrelRotator = (BarrelComponent->GetRightVector()*(-1.f)).Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimRotator - BarrelRotator;

//	UE_LOG(LogTemp, Warning, TEXT("AimRotator.Yaw %f"),AimRotator.Yaw);
//	UE_LOG(LogTemp, Warning, TEXT("BarrelRotator.Yaw %f"),BarrelRotator.Yaw);
	//��BarrelComponent��ʵ�� �ڹ�̧��
	BarrelComponent->Elevate(DeltaRotator.Pitch);

	//�ڼܷ�����ת
	if (FMath::Abs(DeltaRotator.Yaw)<180)
	{
		TurretComponent->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		TurretComponent->Rotate(-DeltaRotator.Yaw);
	}
}

void UTankAimComponent::OnFire()
{
	if (!BarrelComponent || !ProjectileBlueprint)
	{
		UE_LOG(LogTemp, Warning, TEXT("No BarrelComponent or No ProjectileBlueprint"));
		return;
	}
//	UE_LOG(LogTemp, Warning, TEXT("OnFire"));
		//�����ڵ�
	if (AimState != EFiringState::ReLoading )
	{
		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			BarrelComponent->GetSocketLocation(FName("Projectile")),
			BarrelComponent->GetSocketRotation(FName("Projectile"))
			);

		projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}

bool UTankAimComponent::IsLocaked()
{
	if (AimState == EFiringState::Locked)
	{
		return true;
	}
	return false;
}

EFiringState UTankAimComponent::GetAimState() const
{
	return AimState;
}