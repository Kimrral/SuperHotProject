// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeapon_Uzi.h"

// Called when the game starts or when spawned

APlayerWeapon_Uzi::APlayerWeapon_Uzi()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	uziComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("uziComp"));
	uziComp->SetupAttachment(RootComponent);

}

void APlayerWeapon_Uzi::BeginPlay()
{
	Super::BeginPlay();




}

// Called every frame
void APlayerWeapon_Uzi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}