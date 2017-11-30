// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/DamageType.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/RadialForceComponent.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"



// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>("Collision Mesh");
	RootComponent = CollisionMesh;
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovement->bAutoActivate = false;

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//炮弹击中后 取消炮弹射击特效——开始击中特效——隐藏炮弹并取消碰撞
	UE_LOG(LogTemp, Warning, TEXT("I hit it"));
	LaunchBlast->Deactivate();
	ImpactBlast->Activate(true);
	ExplosionForce->Activate(true);
	ExplosionForce->FireImpulse();
	CollisionMesh->SetVisibility(false);
	CollisionMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//
	UGameplayStatics::ApplyRadialDamage
	(
		this,			// 		const UObject * WorldContextObject,
		DamageAmount,	// 		float BaseDamage,
		GetActorLocation(),			// 		const FVector & Origin,
		ExplosionForce->Radius,	// 		float DamageRadius,
		UDamageType::StaticClass(),					// 		TSubclassOf < class UDamageType > DamageTypeClass,
		TArray< AActor *>()		// 预留，暂为空		const TArray < AActor * > & IgnoreActors,
// 		AActor * DamageCauser,
// 		AController * InstigatedByController,
// 		bool bDoFullDamage,
// 		ECollisionChannel DamagePreventionChannel
	);

	MakeNoise(0.5f, NULL, GetActorLocation(), 1000.f);
	//延时Destory
	FTimerHandle Timerhandle;
	GetWorld()->GetTimerManager().SetTimer(Timerhandle, this, &AProjectile::OnTimerExpire, DelayTime, false);
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}

void AProjectile::LaunchProjectile(float speed)
{
	UE_LOG(LogTemp, Warning, TEXT("Finring！"));

//	ProjectileMovement->SetVelocityInLocalSpace(-1.f * FVector::RightVector.GetSafeNormal() * speed);
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector.GetSafeNormal() * speed);
	ProjectileMovement->Activate(true);
}
