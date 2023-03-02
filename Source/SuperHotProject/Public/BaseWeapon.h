// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

enum class EWeaponState : uint8 {
	Idle,
	Fire,
	Reload,
	Destroy,
	Drop,
	PickUp,
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WeaponState)
		EWeaponState mState = EWeaponState::Idle;

	UPROPERTY(VisibleAnywhere, Category = Settgins)
		class USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, Category = Settgins)
		class UStaticMeshComponent* meshComp;

	/*
	UPROPRTY()
	class TSubclassOf<>
	*/


	UFUNCTION();
	virtual void Fire();

	UFUNCTION();
	virtual void Reload();

	

};
