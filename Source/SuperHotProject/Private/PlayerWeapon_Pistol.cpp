// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeapon_Pistol.h"

// Called when the game starts or when spawned
 
APlayerWeapon_Pistol::APlayerWeapon_Pistol()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> gunMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/MilitaryWeapSilver/Weapons/Pistols_A.Pistols_A'"));
	if (gunMesh.Succeeded()) {
		MeshComp->SetSkeletalMesh(gunMesh.Object);
	}

}



void APlayerWeapon_Pistol::BeginPlay()
{
	Super::BeginPlay();




}

// Called every frame
void APlayerWeapon_Pistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}