// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "PlayerWeapon_Uzi.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHOTPROJECT_API APlayerWeapon_Uzi : public ABaseWeapon
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	APlayerWeapon_Uzi();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UStaticMeshComponent* uziComp;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
};
