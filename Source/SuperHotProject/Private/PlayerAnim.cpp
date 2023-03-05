// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "PlayerAnim.h"


void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{

	// 소유 폰 얻어오기
	auto ownerPawn = TryGetPawnOwner();
	// 플레이어로 캐스팅
	auto player = Cast<APlayerCharacter>(ownerPawn);

	if (player != nullptr)
	{
		isWeaponEquipped = player->isWeaponEquipped;
	}
}
