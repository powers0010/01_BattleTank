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
	//��ȡ׼�� BP_Widget
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

	//׼�ĳ�����
	void AimTowardsCrosshair();

	//ͨ�����߼���Ƿ���׼����
	bool GetSightRayHitLocation(FVector & HitLocation);
	//���� ����
	bool GetLookAtDirection(/*FVector2D ScreenLocation, FVector WorldDirection*/);
	//���߼��
	bool GetLookVectorHitLocation(/*FVector Direction, */FVector & HitLocation);

	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5, CrosshairYLocation = 0.25;
	UPROPERTY(EditAnywhere)
		float LineTracRange= 1000000.f;

	//�������������
	FVector CameraWorldLocation = FVector(0.f);
	FVector2D AimScreenLocation = FVector2D(0.f,0.f);
	FVector WorldDirection = FVector(0.f);

	//
	class UTankAimComponent* AimComponent = nullptr;

	virtual void SetPawn(APawn* InPawn) override;
	//���� ����
	UFUNCTION()
		void OnPossesedTankDeath();
};
