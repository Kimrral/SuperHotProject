// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));

	if (tempMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));
	}


	ConstructorHelpers::FObjectFinder<UMaterialInstance> tempMat01(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Characters/Mannequins/Materials/Instances/Manny/MI_Manny_01_Inst.MI_Manny_01_Inst'"));

	if (tempMat01.Succeeded()) {
		GetMesh()->SetMaterial(0, tempMat01.Object);
	}

	ConstructorHelpers::FObjectFinder<UMaterialInstance> tempMat02(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Characters/Mannequins/Materials/Instances/Manny/MI_Manny_02_Inst.MI_Manny_02_Inst'"));

	if (tempMat02.Succeeded()) {
		GetMesh()->SetMaterial(1, tempMat02.Object);
	}

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

