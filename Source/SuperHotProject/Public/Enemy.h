// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Components/PrimitiveComponent.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
		EEnemyWeapon mState = EEnemyWeapon::Gun;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FSMComponent)
		class UEnemyFSM* fsm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSMComponent)
		class UGeometryCollectionComponent* geoComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Settings)
		class USkeletalMeshComponent* gunMeshComp;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
		TSubclassOf<class AActor> bulletFactory;


	UFUNCTION()
		void GunFire();
	

	FORCEINLINE EEnemyWeapon GetEnemyWeapon() { return mState; }
	FORCEINLINE void SetEnemyWeapon(EEnemyWeapon state) { mState = state; }

	UFUNCTION()
		void OnDieAction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
