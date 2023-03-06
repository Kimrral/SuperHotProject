// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyFSM.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->bOrientRotationToMovement = true;

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

	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));

	geoComp = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeoComp"));

	geoComp->SetupAttachment(RootComponent);
	geoComp->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));


	gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComp"));
	gunMeshComp->SetupAttachment(GetMesh());

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	SetEnemyWeapon(mState);


	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnDieAction);

	//geoComp->SetActive(false);
	//geoComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//geoComp->SetVisibility(false);
	
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

void AEnemy::GunFire()
{
	FTransform firePosition = gunMeshComp->GetSocketTransform(TEXT("Muzzle"));

	GetWorld()->SpawnActor<AActor>(bulletFactory, firePosition);

}

void AEnemy::OnDieAction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor->GetName().Contains(TEXT("BP_Projectile"))) {

		GetMesh()->SetVisibility(false);
		geoComp->SetVisibility(true);
		//geoComp->SetActive(true);
		geoComp->AddImpulse(FVector(100,100,100));
		OtherActor->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("bullet"));
	}

	
	
}

