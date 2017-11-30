// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTank.h"
#include "MyTankController.h"
#include "AITankController.h"
#include "Components/InputComponent.h"
#include "Runtime/UMG/Public/Components/WidgetComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
AMyTank::AMyTank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float AMyTank::GetHealthPercent()
{
	return (float)CurrentHealth / (float)MaxHealth;
}

void AMyTank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

float AMyTank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoint = FMath::RoundToInt(Damage);
	int32 DamageToApply = FMath::Clamp<float>(Damage,0.f,CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth<=0)
	{
		UE_LOG(LogTemp, Warning, TEXT("I am Die £¬I am Tank"));
		//´¥·¢Î¯ÍÐ
		OnDeath.Broadcast();
	}

	AAITankController * AIController = Cast<AAITankController>(GetController());
	if (AIController)
	{
		AIController->TankState = EAITankState::EAITankState_MoveAndFire;
	}

//	UE_LOG(LogTemp, Warning, TEXT("DamageToApply: %i"), DamageToApply);
	return DamageToApply;
}

void AMyTank::IncreaseHealth(int32 Amount)
{
	CurrentHealth += Amount;
	CurrentHealth = FMath::Min(CurrentHealth, MaxHealth);
}

