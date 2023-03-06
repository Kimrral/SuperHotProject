// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHOTPROJECT_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()



		virtual void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		bool isWeaponEquipped;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	//	float Pitch;
	
};
