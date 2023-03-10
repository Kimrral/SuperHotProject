// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyFSM.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ActorComponent.h"
#include "BaseWeapon.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/MyeongSeok/PartsoftheBodies/UE4_Mannequin_Head.UE4_Mannequin_Head'"));

	if (tempMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	LeftArm = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftArm"));
	LeftArm->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempLeftArm(TEXT("/Script/Engine.SkeletalMesh'/Game/MyeongSeok/PartsoftheBodies/UE4_Mannequin_Leftarm.UE4_Mannequin_Leftarm'"));
	if (tempLeftArm.Succeeded()) {
		LeftArm->SetSkeletalMesh(tempLeftArm.Object);
	}


	RightArm = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightArm"));
	RightArm->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempRightArm(TEXT("/Script/Engine.SkeletalMesh'/Game/MyeongSeok/PartsoftheBodies/UE4_Mannequin_RightArm.UE4_Mannequin_RightArm'"));
	if (tempRightArm.Succeeded()) {
		RightArm->SetSkeletalMesh(tempRightArm.Object);
	}

	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempBody(TEXT("/Script/Engine.SkeletalMesh'/Game/MyeongSeok/PartsoftheBodies/UE4_Mannequin_Body.UE4_Mannequin_Body'"));
	if (tempBody.Succeeded()) {
		Body->SetSkeletalMesh(tempBody.Object);
	}

	LeftLeg = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftLeg"));
	LeftLeg->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempLeftLeg(TEXT("/Script/Engine.SkeletalMesh'/Game/MyeongSeok/PartsoftheBodies/UE4_Mannequin_LeftLeg.UE4_Mannequin_LeftLeg'"));
	if (tempLeftLeg.Succeeded()) {
		LeftLeg->SetSkeletalMesh(tempLeftLeg.Object);
	}

	RightLeg = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightLeg"));
	RightLeg->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempRightLeg(TEXT("/Script/Engine.SkeletalMesh'/Game/MyeongSeok/PartsoftheBodies/UE4_Mannequin_RightLeg.UE4_Mannequin_RightLeg'"));
	if (tempRightLeg.Succeeded()) {
		RightLeg->SetSkeletalMesh(tempRightLeg.Object);
	}

	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	SetEnemyWeapon(wState);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnDieAction);
	
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
	UE_LOG(LogTemp, Warning, TEXT("Enemy Fire"));


}

void AEnemy::OnDieAction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("BP_Projectile"))) {
		fsm->mState = EEnemyState::Die;
		UE_LOG(LogTemp, Warning, TEXT("Enemy Damage"));
	}

}

