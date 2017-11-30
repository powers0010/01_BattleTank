// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	//Hit 绑定事件//必须为UFNCTION，否则无法产生作用
	UFUNCTION()
	void Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//驱动力
	UPROPERTY(EditDefaultsOnly)
	float TraceMaxDrivingForce = 400000.f;

public:
	//刹车 减速
	UFUNCTION(BlueprintCallable, category = "input")
		void SetThrottle(float Throttle);

	void DriveTrack();
	
	//侧向力 收到侧面攻击
	void ApplySidewayForce();

	//
	float CurrentThrottle;
};
