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

	//发射导弹
	void LaunchProjectile(float speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	//延时时间
	UPROPERTY(EditDefaultsOnly, category = "SetUp")
		float DelayTime = 3.f;
	UPROPERTY(EditDefaultsOnly, category = "SetUp")
		float DamageAmount = 20.f;

private:
	//延时完成 Destory
	void OnTimerExpire();

	class UProjectileMovementComponent * ProjectileMovement = nullptr;
	
protected:
	//碰撞体积
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* CollisionMesh = nullptr;
	//发射特效
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Components")
		class UParticleSystemComponent* LaunchBlast = nullptr;
	//击中特效
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UParticleSystemComponent* ImpactBlast = nullptr;
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class URadialForceComponent* ExplosionForce = nullptr;
};
