// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTankController.h"
#include "TankAimComponent.h"
#include "MyTank.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"


void AMyTankController::BeginPlay()
{
	Super::BeginPlay();
	
	AimComponent = GetPawn()->FindComponentByClass<UTankAimComponent>();
	if (!AimComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("MyController have no AimComponent"));
	}
	if (AimComponent)
	{
		FoundAimConponent(AimComponent);
	}
}

void AMyTankController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossesedTank = Cast<AMyTank>(InPawn);
		if (!PossesedTank)
		{
			return;
		}
		//�󶨴���
		PossesedTank->OnDeath.AddUniqueDynamic(this, &AMyTankController::OnPossesedTankDeath);
	}
}

void AMyTankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//����Ƿ���׼����
	AimTowardsCrosshair();
}

void AMyTankController::AimTowardsCrosshair()
{
	if (!GetPawn())
	{
//		UE_LOG(LogTemp, Warning, TEXT("I Can not Get Tank"));
		return;
	}
	//����Ƿ���׼ ����
	FVector HitLocation = FVector(1.f);

	//���߼��
	if (GetSightRayHitLocation(HitLocation))
	{
		AimComponent->AimAt(HitLocation);
	}
}

void AMyTankController::SetAimImage(UUserWidget* AimImageToSet)
{
	if (!AimImageToSet)
	{
		return;
	}
	AimImage = AimImageToSet;
}


bool AMyTankController::GetSightRayHitLocation(FVector & HitLocation)
{
	int32 ViewportSizeX, ViewportSizeY;

	//����ߴ� 1920*1080��	//���ݱ�������׼������Ļ������
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	AimScreenLocation.X = ViewportSizeX*CrosshairXLocation;
	AimScreenLocation.Y = ViewportSizeY*CrosshairYLocation;
//	(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrosshairYLocation);

	//��Ļ����ת��Ϊ�ռ�����,��ȡ�ӽǷ���
	
	if (GetLookAtDirection(/*AimScreenLocation, WorldDirection*/))
	{
//		UE_LOG(LogTemp, Warning, TEXT("WorldDirection is %s"), *WorldDirection.ToString());

		if (GetLookVectorHitLocation(/*WorldDirection, */HitLocation))		//���߼��
		{
//			UE_LOG(LogTemp, Warning, TEXT("HitLocation is %s"), *HitLocation.ToString());
/*			GetControlledTank()->AimAt(HitLocation);*/
		}
	}
	//
	return true;
}

bool AMyTankController::GetLookAtDirection(/*FVector2D ScreenLocation, FVector WorldDirection*/) 
{
//	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld
	(
		AimScreenLocation.X,
		AimScreenLocation.Y,
		CameraWorldLocation, 
		WorldDirection
	);
}

bool AMyTankController::GetLookVectorHitLocation(/*FVector Direction,*/FVector & HitLocation)
{
	FHitResult OutHit;
//	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
//	FVector EndLocation = StartLocation + (Direction * LineTracRange);
	FVector EndLocation = CameraWorldLocation + (WorldDirection.GetSafeNormal() * LineTracRange);

	const FCollisionQueryParams Params(FName(TEXT("TRACE")),false,GetPawn());

	const FCollisionResponseParams ResponseParam;

		 
	if (GetWorld()->LineTraceSingleByChannel(
				OutHit,
				CameraWorldLocation,
				EndLocation,
				ECollisionChannel::ECC_Visibility,
				Params,
				ResponseParam
			)
		)
	{
		HitLocation = OutHit.Location;

		return true;
	}

//	UE_LOG(LogTemp, Warning, TEXT("Failed to GetLookVectorHitLocation"));
	return false;
}

void AMyTankController::OnPossesedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("I am dead , I am PlayerController"));
	AMyTank* MyTank = Cast<AMyTank>(GetPawn());
	if (!MyTank)
	{
		return;
	}
	//GetPawn()->DetachFromControllerPendingDestroy();
	MyTank->DisableInput(this);
	MyTank->DestoryTankAfterDeath();
}