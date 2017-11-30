// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimComponent.generated.h"

class UTankBarrel;	//ǰ������
class UTankTurret;
class AProjectile;

//�ڵ�����
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
	//��׼
	void AimAt(FVector HitLocation);

	bool IsLocaked();
private:
	//�ڵ��ٶ�
	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 100000;

	UTankBarrel* BarrelComponent = nullptr;
	UTankTurret* TurretComponent = nullptr;
	//�ƶ��ڹ� ����׼��
	void MoveBarrelTowards(FVector AimDirection);

	//��ȡ�ڵ���
	TSubclassOf<AProjectile> GetProjectileBlueprint();
	//�ڵ���
	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	//��¼��һ�ι���ʱ��
	double LastFireTime = 10.f;

	UPROPERTY(EditAnywhere)
		float ReloadFireTime = 3.f;
	//״̬����׼ ���� ����CD
	UPROPERTY(VisibleAnywhere , category = "AimState")
	EFiringState AimState = EFiringState::Aiming;


	//�Ƿ��Ѿ���׼
	bool IsBarrelMoving();

	//��¼��׼����
	FVector AimDirection = FVector(0.f);
};
