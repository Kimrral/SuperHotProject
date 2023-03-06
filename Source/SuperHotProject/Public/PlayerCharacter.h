// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SUPERHOTPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "VRCamera")
	class UCameraComponent* VRCamera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 회전처리 함수
	void Turn(const FInputActionValue& Values);
	// 이동처리 함수
	void Move(const FInputActionValue& Values);
	void MoveReleased();
	void Jump();
	void JumpEnd();
	void Fire();
	void Throw();
	void Unequip();
	UFUNCTION(BlueprintCallable)
	bool IsMoving();
	UFUNCTION(BlueprintImplementableEvent)
	void ResetFireCooldown();
	UFUNCTION()
		void DetachWeapon();

	// 필요속성 : 이동속도, 입력액션, 입력매핑컨텍스트
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		float moveSpeed = 500.0f;
	// Input Mapping Context
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		class UInputMappingContext* IMC_Default;
	// Input Action for Move
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		class UInputAction* IA_Move;
	// 마우스 입력처리
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		class UInputAction* IA_Look;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		class UInputAction* IA_Jump;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		class UInputAction* IA_Fire;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		class UInputAction* IA_Throw;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		class UInputAction* IA_Unequip;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float XMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float YMovement;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		class USoundBase* pistolPickup;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		TSubclassOf<class UUserWidget> crosshairFactory;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		TSubclassOf<class AActor> BPProjectile;	
	UPROPERTY(BlueprintReadOnly)
		class UUserWidget* crosshairUI;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float TimeDilation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float Alpha;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeBetweenShots = 0.4f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bTestTime = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isWeaponEquipped = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bCanFire = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool isMontagePlaying;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	class UAnimMontage* punchMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	class USoundBase* pistol_fire;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	class USoundBase* pistol_pickup;

	



};
