// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "PlayerAnim.h"


void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{

	// ���� �� ������
	auto ownerPawn = TryGetPawnOwner();
	// �÷��̾�� ĳ����
	auto player = Cast<APlayerCharacter>(ownerPawn);

	if (player != nullptr)
	{
		isWeaponEquipped = player->isWeaponEquipped;
	}
}
