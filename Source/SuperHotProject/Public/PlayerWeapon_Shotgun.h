// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "PlayerWeapon_Shotgun.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHOTPROJECT_API APlayerWeapon_Shotgun : public ABaseWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerWeapon_Shotgun();


	UPROPERTY(EditAnywhere, Category = Settings)
		class UStaticMeshComponent* shotgunComp;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	
};
