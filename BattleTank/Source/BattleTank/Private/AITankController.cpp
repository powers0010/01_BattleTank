// Fill out your copyright notice in the Description page of Project Settings.

#include "AITankController.h"
#include "TankAimComponent.h"
#include "MyTank.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"

AAITankController::AAITankController()
{
	AITankBehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>("AITankBehaviorTree");
	AITankBlackboard = CreateDefaultSubobject<UBlackboardComponent>("AITankBlackboard");
}

void AAITankController::BeginPlay()
{
	Super::BeginPlay();

	APawn* Playertank = GetPawn();
	if (!Playertank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Can not find Player"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Can find Player"));
	}
}

void AAITankController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossesedTank = Cast<AMyTank>(InPawn);
		if (!PossesedTank)
		{
			return;
		}
		//绑定代理
		PossesedTank->OnDeath.AddUniqueDynamic(this, &AAITankController::OnPossesedTankDeath);
	}
}

void AAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (TankState)
	{
	case EAITankState::EAITankState_Wait:
	
		break;
	case  EAITankState::EAITankState_MoveAndFire:
		MoveAndFire();
		break;
	case EAITankState::EAITankState_Fire:
		FireWithOutMove();
		break;
	default:
		break;
	}
}

void AAITankController::MoveAndFire()
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledPawn = GetPawn();

	if (!PlayerTank || !ControlledPawn) { return; }
	//向玩家移动
//	MoveToLocation(PlayerTank->GetActorLocation(), AcceptRadiu);
//	UE_LOG(LogTemp, Warning, TEXT("ActorLocation: %s"), *PlayerTank->GetActorLocation().ToString());
	MoveToActor(PlayerTank, AcceptRadiu, true);

	//	FString Name = PlayerTank->GetName();
	//	UE_LOG(LogTemp, Warning, TEXT("PlayerTank: %s"),*Name);

	auto AimComponent = ControlledPawn->FindComponentByClass<UTankAimComponent>();
	//瞄准玩家
	AimComponent->AimAt(PlayerTank->GetActorLocation());

	// 	//瞄准后 开火
	if (AimComponent->IsLocaked())
	{
		AimComponent->OnFire();
	}
}

void AAITankController::FireWithOutMove()
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledPawn = GetPawn();

	if (!PlayerTank || !ControlledPawn) { return; }

	auto AimComponent = ControlledPawn->FindComponentByClass<UTankAimComponent>();
	//瞄准玩家
	AimComponent->AimAt(PlayerTank->GetActorLocation());
	if (AimComponent->IsLocaked())
	{
		AimComponent->OnFire();
	}
}

void AAITankController::OnPossesedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("I am dead , I am AI"));

	AMyTank* MyTank = Cast<AMyTank>(GetPawn());
	if (!MyTank)
	{
		return;
	}
	MyTank->DetachFromControllerPendingDestroy();
	MyTank->DestoryTankAfterDeath();
}