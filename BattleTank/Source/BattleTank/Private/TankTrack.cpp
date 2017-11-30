// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::Hit);
}

void UTankTrack::Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
//	UE_LOG(LogTemp, Warning, TEXT("I am hit"));
	//接触地面才能驱动
	DriveTrack();
	ApplySidewayForce();
	CurrentThrottle = 0.f;
}


void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.f, 1.f);
}

void UTankTrack::DriveTrack()
{
//	FVector ForceApplied = -1.f * CurrentThrottle * TraceMaxDrivingForce * GetRightVector();
	FVector ForceApplied = CurrentThrottle * TraceMaxDrivingForce * GetForwardVector();
	FVector ForceLocation = GetSocketLocation("ForceLocation");
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::ApplySidewayForce()
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	float SlippageSpeed = FVector::DotProduct(GetForwardVector(), GetComponentVelocity());
	FVector Accelerate = -SlippageSpeed / DeltaTime * GetForwardVector();

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CurForce = Accelerate*TankRoot->GetMass() / 2;
//	TankRoot->AddForce(CurForce);
}
