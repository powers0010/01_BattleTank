// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpItem.generated.h"

UCLASS()
class BATTLETANK_API APickUpItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//��ײ����
	UPROPERTY(EditDefaultsOnly,category = "Collision")
		class UStaticMeshComponent* StatciMesh = nullptr;
	UPROPERTY(EditDefaultsOnly,category = "Collision")
		class USphereComponent* SphereCollision = nullptr;
public:	

	
};
