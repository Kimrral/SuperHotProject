// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeapon_Shotgun.h"


// Called when the game starts or when spawned

APlayerWeapon_Shotgun::APlayerWeapon_Shotgun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	shotgunComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("shotgunComp"));
	shotgunComp->SetupAttachment(RootComponent);
	
}

void APlayerWeapon_Shotgun::BeginPlay()
{
	Super::BeginPlay();


	

}

// Called every frame
void APlayerWeapon_Shotgun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}