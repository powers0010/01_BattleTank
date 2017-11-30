// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITankController.generated.h"


/**
 * 
 */
//定义AITank的状态
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
	//移动 和 攻击
	UFUNCTION(BlueprintCallable, category = "Target")
		void MoveAndFire();
	UFUNCTION(BlueprintCallable, category = "Target")
	void FireWithOutMove();
protected:
	//追踪玩家的可接收距离
	UPROPERTY(EditAnywhere, category = "SetUp")
		float AcceptRadiu = 5000.f;
	//攻击间隔
	UPROPERTY(EditAnywhere, category = "SetUp")
		float ReloadFireTime = 3.f;


private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//死亡 函数
	UFUNCTION()
		void OnPossesedTankDeath();

	virtual void SetPawn(APawn* InPawn) override;

private:
	//----------AI相关
	//由于需要每帧使用，需要设置属性为Transient//该属性为临时属性。不应被保存，在载入时会被填零。
	UPROPERTY(Transient)	
	class UBehaviorTreeComponent* AITankBehaviorTree = nullptr;
	UPROPERTY(Transient)
	class UBlackboardComponent* AITankBlackboard = nullptr;

};
