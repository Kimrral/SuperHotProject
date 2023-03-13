// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyFSM.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ActorComponent.h"
#include "BaseWeapon.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"


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

	HeadComp = CreateDefaultSubobject<UBoxComponent>(TEXT("HeadComp"));
	HeadComp->SetupAttachment(GetMesh(),"headSocket");
	HeadComp->SetBoxExtent(FVector(10, 10, 10));
	HeadComp->SetRelativeLocation(FVector(0, 0, 170));

	LeftArm = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftArm"));
	LeftArm->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempLeftArm(TEXT("/Script/Engine.SkeletalMesh'/Game/MyeongSeok/PartsoftheBodies/UE4_Mannequin_Leftarm.UE4_Mannequin_Leftarm'"));
	if (tempLeftArm.Succeeded()) {
		LeftArm->SetSkeletalMesh(tempLeftArm.Object);
	}

	LeftArmComp = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftArmComp"));
	LeftArmComp->SetupAttachment(LeftArm,"root");
	LeftArmComp->SetBoxExtent(FVector(8, 30, 15));
	LeftArmComp->SetRelativeLocation(FVector(10, 30, 150));

	RightArm = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightArm"));
	RightArm->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempRightArm(TEXT("/Script/Engine.SkeletalMesh'/Game/MyeongSeok/PartsoftheBodies/UE4_Mannequin_RightArm.UE4_Mannequin_RightArm'"));
	if (tempRightArm.Succeeded()) {
		RightArm->SetSkeletalMesh(tempRightArm.Object);
	}

	RightArmComp = CreateDefaultSubobject<UBoxComponent>(TEXT("RightArmComp"));
	RightArmComp->SetupAttachment(RightArm,"root");
	RightArmComp->SetBoxExtent(FVector(8, 39, 15));
	RightArmComp->SetRelativeLocation(FVector(-20, 20, 140));

	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempBody(TEXT("/Script/Engine.SkeletalMesh'/Game/MyeongSeok/PartsoftheBodies/UE4_Mannequin_Body.UE4_Mannequin_Body'"));
	if (tempBody.Succeeded()) {
		Body->SetSkeletalMesh(tempBody.Object);
	}

	BodyComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyComp"));
	BodyComp->SetupAttachment(Body);
	BodyComp->SetBoxExtent(FVector(20, 20, 20));
	BodyComp->SetRelativeLocation(FVector(0, 0, 130));


	LeftLeg = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftLeg"));
	LeftLeg->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempLeftLeg(TEXT("/Script/Engine.SkeletalMesh'/Game/MyeongSeok/PartsoftheBodies/UE4_Mannequin_LeftLeg.UE4_Mannequin_LeftLeg'"));
	if (tempLeftLeg.Succeeded()) {
		LeftLeg->SetSkeletalMesh(tempLeftLeg.Object);
	}

	LeftLegComp = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftLegComp"));
	LeftLegComp->SetupAttachment(LeftLeg, "thigh_lSocket");
	LeftLegComp->SetBoxExtent(FVector(10, 17, 45));
	LeftLegComp->SetRelativeLocation(FVector(13, 0, 45));


	RightLeg = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightLeg"));
	RightLeg->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempRightLeg(TEXT("/Script/Engine.SkeletalMesh'/Game/MyeongSeok/PartsoftheBodies/UE4_Mannequin_RightLeg.UE4_Mannequin_RightLeg'"));
	if (tempRightLeg.Succeeded()) {
		RightLeg->SetSkeletalMesh(tempRightLeg.Object);
	}

	RightLegComp = CreateDefaultSubobject<UBoxComponent>(TEXT("RightLegComp"));
	RightLegComp->SetupAttachment(RightLeg,"thigh_rSocket");
	RightLegComp->SetBoxExtent(FVector(11, 15, 45));
	RightLegComp->SetRelativeLocation(FVector(-11, 0, 49));


	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(GetMesh(), "Weapon_R");

	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	SetEnemyWeapon(wState);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnDieAction);
	HeadComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnHitHeadAction);
	LeftArmComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnHitLeftArmAction);
	RightArmComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnHitRightArmAction);
	BodyComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnHitBodyAction);
	LeftLegComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnHitLeftlegAction);
	RightLegComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnHitRightlegAction);

	
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

	if (GetEnemyWeapon() == EEnemyWeapon::Gun) {
		FTransform socketTrans = GunMesh->GetSocketTransform(TEXT("FireSocket"));
		FVector fireLoc = socketTrans.GetLocation();
		FRotator fireRot = socketTrans.GetRotation().Rotator();
		FTransform fireTrans = UKismetMathLibrary::MakeTransform(fireLoc,fireRot);
		GetWorld()->SpawnActor<AActor>(bulletFactory, fireTrans);
	}
}

void AEnemy::OnDieAction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor->GetName().Contains(TEXT("BP_Projectile"))) {
		/*
		if (GetEnemyWeapon() == EEnemyWeapon::Gun) {
			GetWorld()->SpawnActor<ABaseWeapon>(WeaponFactroy, GetActorTransform());
		}
		fsm->mState = EEnemyState::Die;
		*/
		UE_LOG(LogTemp, Warning, TEXT("Enemy Damage"));
	}

}

void AEnemy::OnHitHeadAction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("BP_Player"))) {
		fsm->mState = EEnemyState::Die;
		UE_LOG(LogTemp, Warning, TEXT("Head Hit"));
	}

	if (OtherActor->GetName().Contains(TEXT("BP_Punch"))) {
		bHitHead = true;
		UE_LOG(LogTemp, Warning, TEXT("Punch Head Hit"));
	}
}

void AEnemy::OnHitBodyAction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("BP_Player"))) {
		fsm->mState = EEnemyState::Die;
		UE_LOG(LogTemp, Warning, TEXT("Body Hit"));
	}

	if (OtherActor->GetName().Contains(TEXT("BP_Punch"))) {
		bHitBody = true;
		UE_LOG(LogTemp, Warning, TEXT("Punch Body Hit"));
	}
}

void AEnemy::OnHitLeftArmAction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("BP_Player"))) {
		fsm->mState = EEnemyState::Die;
		UE_LOG(LogTemp, Warning, TEXT("LeftArm Hit"));
	}

	if (OtherActor->GetName().Contains(TEXT("BP_Punch"))) {
		bHitLeftArm = true;
		UE_LOG(LogTemp, Warning, TEXT("Punch LeftArm Hit"));
	}
}

void AEnemy::OnHitLeftlegAction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("BP_Player"))) {
		fsm->mState = EEnemyState::Die;
		UE_LOG(LogTemp, Warning, TEXT("LeftLeg Hit"));
	}

	if (OtherActor->GetName().Contains(TEXT("BP_Punch"))) {
		bHitLeftleg = true;
		UE_LOG(LogTemp, Warning, TEXT("Punch LeftLeg Hit"));
	}
}

void AEnemy::OnHitRightArmAction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("BP_Player"))) {
		fsm->mState = EEnemyState::Die;
		UE_LOG(LogTemp, Warning, TEXT("RightArm Hit"));
	}

	if (OtherActor->GetName().Contains(TEXT("BP_Punch"))) {
		bHitRightArm = true;
		UE_LOG(LogTemp, Warning, TEXT("Punch RightArm Hit"));
	}
}

void AEnemy::OnHitRightlegAction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("BP_Player"))) {
		fsm->mState = EEnemyState::Die;
		UE_LOG(LogTemp, Warning, TEXT("RightLeg Hit"));
	}

	if (OtherActor->GetName().Contains(TEXT("BP_Punch"))) {
		bHitRightleg = true;
		UE_LOG(LogTemp, Warning, TEXT("Punch RightLeg Hit"));
	}
}


