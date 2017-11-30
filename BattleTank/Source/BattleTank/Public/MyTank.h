// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyTank.generated.h"

class AProjectile;

//代理宏
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);


UCLASS()
class BATTLETANK_API AMyTank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyTank();

	//造成伤害的时候调用
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure , category = "Health")
	float GetHealthPercent();

	//代理
	FTankDelegate OnDeath;
public:	
//
	virtual void BeginPlay() override;

	//Health
	UPROPERTY(EditAnywhere , BlueprintReadWrite, category = "SetUp")
	int32 MaxHealth = 100.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "SetUp")
	int32 CurrentHealth = MaxHealth;
	UFUNCTION(BlueprintCallable, category = "Health")
		void IncreaseHealth(int32 Amount);

	UFUNCTION(BlueprintImplementableEvent, category = "Death")
		void DestoryTankAfterDeath();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,category = "Widget")
		class UWidgetComponent* HealthBar;
};
