// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	//���䵼��
	void LaunchProjectile(float speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	//��ʱʱ��
	UPROPERTY(EditDefaultsOnly, category = "SetUp")
		float DelayTime = 3.f;
	UPROPERTY(EditDefaultsOnly, category = "SetUp")
		float DamageAmount = 20.f;

private:
	//��ʱ��� Destory
	void OnTimerExpire();

	class UProjectileMovementComponent * ProjectileMovement = nullptr;
	
protected:
	//��ײ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* CollisionMesh = nullptr;
	//������Ч
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Components")
		class UParticleSystemComponent* LaunchBlast = nullptr;
	//������Ч
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UParticleSystemComponent* ImpactBlast = nullptr;
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class URadialForceComponent* ExplosionForce = nullptr;
};
