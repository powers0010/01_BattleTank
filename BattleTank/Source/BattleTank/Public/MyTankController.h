// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyTankController.generated.h"

class UUserWidget;
/**
 * 
 */

UCLASS()
class BATTLETANK_API AMyTankController : public APlayerController
{
	GENERATED_BODY()

public:
	//获取准心 BP_Widget
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UUserWidget * AimImage = nullptr;

	UFUNCTION(BlueprintCallable , category = "Setup")
		void SetAimImage(UUserWidget* AimImageToSet);
	//FindAimComponent
	UFUNCTION(BlueprintImplementableEvent, category = "SetUp")
		void FoundAimConponent(UTankAimComponent * AimComREF);

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//准心朝向检测
	void AimTowardsCrosshair();

	//通过射线检测是否瞄准敌人
	bool GetSightRayHitLocation(FVector & HitLocation);
	//计算 方向
	bool GetLookAtDirection(/*FVector2D ScreenLocation, FVector WorldDirection*/);
	//射线检测
	bool GetLookVectorHitLocation(/*FVector Direction, */FVector & HitLocation);

	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5, CrosshairYLocation = 0.25;
	UPROPERTY(EditAnywhere)
		float LineTracRange= 1000000.f;

	//摄像机世界坐标
	FVector CameraWorldLocation = FVector(0.f);
	FVector2D AimScreenLocation = FVector2D(0.f,0.f);
	FVector WorldDirection = FVector(0.f);

	//
	class UTankAimComponent* AimComponent = nullptr;

	virtual void SetPawn(APawn* InPawn) override;
	//死亡 函数
	UFUNCTION()
		void OnPossesedTankDeath();
};
