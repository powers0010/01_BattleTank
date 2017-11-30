// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITankController.generated.h"


/**
 * 
 */
//����AITank��״̬
UENUM(Blueprintable)
enum class EAITankState:uint8
{
	EAITankState_Wait,
	EAITankState_Fire,
	EAITankState_MoveAndFire,
};


UCLASS()
class BATTLETANK_API AAITankController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAITankController();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Target")
		EAITankState TankState = EAITankState::EAITankState_Wait;
	//�ƶ� �� ����
	UFUNCTION(BlueprintCallable, category = "Target")
		void MoveAndFire();
	UFUNCTION(BlueprintCallable, category = "Target")
	void FireWithOutMove();
protected:
	//׷����ҵĿɽ��վ���
	UPROPERTY(EditAnywhere, category = "SetUp")
		float AcceptRadiu = 5000.f;
	//�������
	UPROPERTY(EditAnywhere, category = "SetUp")
		float ReloadFireTime = 3.f;


private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//���� ����
	UFUNCTION()
		void OnPossesedTankDeath();

	virtual void SetPawn(APawn* InPawn) override;

private:
	//----------AI���
	//������Ҫÿ֡ʹ�ã���Ҫ��������ΪTransient//������Ϊ��ʱ���ԡ���Ӧ�����棬������ʱ�ᱻ���㡣
	UPROPERTY(Transient)	
	class UBehaviorTreeComponent* AITankBehaviorTree = nullptr;
	UPROPERTY(Transient)
	class UBlackboardComponent* AITankBlackboard = nullptr;

};
