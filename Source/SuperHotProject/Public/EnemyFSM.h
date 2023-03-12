// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"


UENUM(BlueprintType)
enum class EEnemyState : uint8 {
	Idle,
	Move,
	FistAttack,
	GunAttack,
	Die,
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERHOTPROJECT_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = FSM)
		EEnemyState mState = EEnemyState::Idle;

	void IdleState();
	void MoveState();
	void FistAttackState();
	void GunAttackState();
	void DieState();


	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float idleDelayTime = 2;

	float currentTime = 0;

	UPROPERTY(VisibleAnywhere, Category = FSM)
		class APlayerCharacter* target;

	UPROPERTY()
		class AEnemy* me;

	UPROPERTY(EditDefaultsOnly, Category = FSM)
		bool bHasGun = false;

	UPROPERTY(EditDefaultsOnly, Category = FSM)
		float attackRange = 150.0f;

	UPROPERTY(EditDefaultsOnly, Category = FSM)
		float shotRange = 600.0f;

	UPROPERTY(EditDefaultsOnly, Category = FSM)
		float attackDelayTime = 2.0f;

	UFUNCTION(BlueprintCallable)
	void OnDamage();

	UPROPERTY(EditDefaultsOnly, Category = FSM)
	bool bTestMove = false;

	UPROPERTY()
		class UEnemyAnim* anim;

	UPROPERTY()
		class AAIController* ai;



};
