// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8 {
	Idle,       // 초기상태
	Equipped,   // 장착상태
	Pickup     // 그랩 할 수 있는 상태
};

UCLASS()
class SUPERHOTPROJECT_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, Category = Settings)
	float FireRate = 0.5f;

	UPROPERTY(EditAnywhere, Category = WeaponState)
	EWeaponState mState = EWeaponState::Idle;

	FTimerHandle FireTimerHandle;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settgins)
		class USkeletalMeshComponent* MeshComp;

	UFUNCTION(BlueprintCallable)
	virtual void DoFire();

	UFUNCTION(BlueprintCallable)
	virtual void FirePressed();

	UFUNCTION(BlueprintCallable)
	virtual void FireRelease();

	UPROPERTY(EditDefaultsOnly, Category = Bullet)
		TSubclassOf<class AActor> bulletFactory;

	
	FORCEINLINE float GetFireRate() { return FireRate; }
	FORCEINLINE void SetFireRate(float rate) { FireRate = rate <= 0 ? 0.5 : rate; }

	FORCEINLINE EWeaponState GetWeaponState() { return mState; }
	FORCEINLINE void SetWeaponState(EWeaponState state) { mState = state; }

	FORCEINLINE FTimerHandle GetFireTimerHandle() { return FireTimerHandle; }
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = Bullet)
		class UNiagaraSystem* NA_SmokeRing;

};
