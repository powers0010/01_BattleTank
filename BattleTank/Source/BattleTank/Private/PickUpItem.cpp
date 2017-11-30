// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpItem.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"

// Sets default values
APickUpItem::APickUpItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StatciMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollison");
	SphereCollision->InitSphereRadius(50.f);
}

// Called when the game starts or when spawned
void APickUpItem::BeginPlay()
{
	Super::BeginPlay();
	
}


