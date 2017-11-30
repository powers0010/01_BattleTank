// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimComponent.generated.h"

class UTankBarrel;	//前置申明
class UTankTurret;
class AProjectile;

//炮弹加载
UENUM(Blueprintable)
enum class EFiringState : uint8
{
	ReLoading = 0,
	Aiming = 1,
	Locked = 2,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;


	UFUNCTION(BlueprintCallable, category = "Input")
		void Initalize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, category = "Input")
		void OnFire();

	UFUNCTION(BlueprintCallable, category = "AimState")
	EFiringState GetAimState() const;
public:	
	//瞄准
	void AimAt(FVector HitLocation);

	bool IsLocaked();
private:
	//炮弹速度
	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 100000;

	UTankBarrel* BarrelComponent = nullptr;
	UTankTurret* TurretComponent = nullptr;
	//移动炮管 （瞄准）
	void MoveBarrelTowards(FVector AimDirection);

	//获取炮弹类
	TSubclassOf<AProjectile> GetProjectileBlueprint();
	//炮弹类
	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	//记录上一次攻击时间
	double LastFireTime = 10.f;

	UPROPERTY(EditAnywhere)
		float ReloadFireTime = 3.f;
	//状态：瞄准 保持 攻击CD
	UPROPERTY(VisibleAnywhere , category = "AimState")
	EFiringState AimState = EFiringState::Aiming;


	//是否已经瞄准
	bool IsBarrelMoving();

	//记录瞄准方向
	FVector AimDirection = FVector(0.f);
};
