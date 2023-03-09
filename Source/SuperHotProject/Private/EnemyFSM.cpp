// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "PlayerCharacter.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());
	target = Cast<APlayerCharacter>(actor);

	me = Cast<AEnemy>(GetOwner());


}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	switch (mState) {
		case EEnemyState::Idle:
			IdleState();
			break;
		case EEnemyState::Move:
			MoveState();
			break;
		case EEnemyState::FistAttack:
			FistAttackState();
			break;
		case EEnemyState::GunAttack:
			GunAttackState();
			break;
		case EEnemyState::Die:
			DieState();
			break;
		default:
			break;
	}
}

void UEnemyFSM::IdleState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime > idleDelayTime) {
		mState = EEnemyState::Move;
		currentTime = 0;
	}
}

void UEnemyFSM::MoveState()
{
	if (bTestMove) {
		return;
	}
	FVector destination = target->GetActorLocation();
	FVector dir = destination - me->GetActorLocation();
	me->AddMovementInput(dir.GetSafeNormal());
	UE_LOG(LogTemp, Warning, TEXT("Run"));

	// 나중에 리팩토링 해야함 Enemy 클래스에 무기 Enum State 클래스 존재
	if (me->GetEnemyWeapon() == EEnemyWeapon::Fist) {
		if (dir.Size() < attackRange) {
			mState = EEnemyState::FistAttack;
		}
	}
	else if(me->GetEnemyWeapon() == EEnemyWeapon::Gun){
		if (dir.Size() < shotRange) {
			mState = EEnemyState::GunAttack;
		}
	}

}

void UEnemyFSM::FistAttackState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > attackDelayTime) {
		UE_LOG(LogTemp, Warning, TEXT("FistAttack"));
		currentTime = 0;
	}

	float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());

	if (distance > attackRange) {
		mState = EEnemyState::Move;
	}
}

void UEnemyFSM::GunAttackState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > attackDelayTime) {
		UE_LOG(LogTemp, Warning, TEXT("Fire"));
		me->GunFire();
		currentTime = 0;
	}

	float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());

	if (distance > shotRange) {
		mState = EEnemyState::Move;
	}
}

void UEnemyFSM::DieState()
{
	//me->Destroy();
	//me->GetMesh()->SetSimulatePhysics(true);
}

void UEnemyFSM::OnDamage()
{
	mState = EEnemyState::Die;
}

