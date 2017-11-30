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
	//Hit ���¼�//����ΪUFNCTION�������޷���������
	UFUNCTION()
	void Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//������
	UPROPERTY(EditDefaultsOnly)
	float TraceMaxDrivingForce = 400000.f;

public:
	//ɲ�� ����
	UFUNCTION(BlueprintCallable, category = "input")
		void SetThrottle(float Throttle);

	void DriveTrack();
	
	//������ �յ����湥��
	void ApplySidewayForce();

	//
	float CurrentThrottle;
};
