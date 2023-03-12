// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UENUM(BlueprintType)
enum class EEnemyWeapon : uint8 {
	Idle,
	Fist,
	Gun,
};


UCLASS()
class SUPERHOTPROJECT_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = FSM)
		EEnemyWeapon wState = EEnemyWeapon::Idle;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSMComponent)
		class UEnemyFSM* fsm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Settings)
		class USkeletalMeshComponent* LeftArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Settings)
		class USkeletalMeshComponent* RightArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Settings)
		class USkeletalMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Settings)
		class USkeletalMeshComponent* LeftLeg;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Settings)
		class USkeletalMeshComponent* RightLeg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UBoxComponent* HeadComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UBoxComponent* LeftArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UBoxComponent* RightArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UBoxComponent* BodyComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UBoxComponent* LeftLegComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UBoxComponent* RightLegComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class USkeletalMeshComponent* GunMesh;



	UPROPERTY(EditDefaultsOnly, Category = Settings)
		TSubclassOf<class AActor> bulletFactory;


	UPROPERTY(EditDefaultsOnly, Category = Settings)
		TSubclassOf<class ABaseWeapon> WeaponFactroy;



	UFUNCTION()
		void GunFire();	

	FORCEINLINE EEnemyWeapon GetEnemyWeapon() { return wState; }
	FORCEINLINE void SetEnemyWeapon(EEnemyWeapon state) { wState = state; }

	UFUNCTION()
		void OnDieAction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void Die();
};
