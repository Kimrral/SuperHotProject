// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "PlayerWeapon_Pistol.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHOTPROJECT_API APlayerWeapon_Pistol : public ABaseWeapon
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APlayerWeapon_Pistol();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Settings)
		class USkeletalMeshComponent* pistolComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UBoxComponent* traceCheckBox;

	//UFUNCTION()
		//void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION()
		//void DetachWeapon();

	UFUNCTION()
	void PickUpC();
};
