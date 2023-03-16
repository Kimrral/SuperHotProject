// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VRGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SUPERHOTPROJECT_API AVRGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
	TArray<class AEnemy*> enemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		int32 totalEnemy = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		bool bClear = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		bool bSpawn = false;
	
};
