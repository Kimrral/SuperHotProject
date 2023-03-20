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
	void FireReleased();
	void FireLeft();
	void Throw();
	void Unequip();
	UFUNCTION(BlueprintCallable)
	bool IsMoving();
	UFUNCTION(BlueprintImplementableEvent)
	void ResetFireCooldown();
	UFUNCTION(BlueprintImplementableEvent)
		void ResetFireCooldownLeft();
	UFUNCTION(BlueprintImplementableEvent)
	void ResetUziFireCooldown();
	UFUNCTION(BlueprintImplementableEvent)
		void DetachPistol();
	UFUNCTION(BlueprintImplementableEvent)
		void SpawnShotgunBullet();
	UFUNCTION(BlueprintImplementableEvent)
		void SpawnPistolBullet();
	UFUNCTION(BlueprintImplementableEvent)
		void SpawnUziBullet();
	UFUNCTION(BlueprintImplementableEvent)
		void SpawnUziBulletLeft();
	UFUNCTION()
	void DetachWeapon();
	UFUNCTION()
		void Attach();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
		class UBoxComponent* attachBoxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
		class UBoxComponent* attachBoxCompL;


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
		class UInputAction* IA_FireL;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		class UInputAction* IA_Throw;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		class UInputAction* IA_Unequip;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		class UInputAction* IA_Attach;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float XMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float YMovement;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		class USoundBase* pistolPickup;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		class USoundBase* OutOfAmmo;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		TSubclassOf<class UUserWidget> crosshairFactory;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		TSubclassOf<class UUserWidget> noAmmoFactory;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		TSubclassOf<class AActor> BPProjectile;	
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		TSubclassOf<class AActor> BPNoAmmoUI;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		TSubclassOf<class AActor> BPPunchBoxComp;
	UPROPERTY(BlueprintReadOnly)
		class UUserWidget* crosshairUI;
	UPROPERTY(BlueprintReadOnly)
		class UUserWidget* noAmmoUI;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isLeftWeaponEquipped = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isUsingShotgun = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isUsingShotgunLeft = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isUsingUzi = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isUsingUziLeft = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bCanFire = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bCanFireLeft = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool isEnterUIEnd = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool isMontagePlaying;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	class UAnimMontage* punchMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	class USoundBase* pistol_fire;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		class USoundBase* shotgun_fire;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	class USoundBase* pistol_pickup;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* fireSmokeFactory;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//class APlayerWeapon_Pistol* Pistol;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		TSubclassOf<class APlayerWeapon_Pistol> pistolFactory;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MotionController")
		class UMotionControllerComponent* LeftHand;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MotionController")
		class UMotionControllerComponent* RightHand;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MotionController")
		class USkeletalMeshComponent* LeftHandMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MotionController")
		class USkeletalMeshComponent* RightHandMesh;
	// 집게손가락 표시할 모션컨트롤러
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HandComp", meta = (AllowPrivateAccess = true))
		class UMotionControllerComponent* RightAim;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
		class UInputMappingContext* IMC_Hand;

	//UPROPERTY()
		//class APlayerWeapon_Uzi* uziRef;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		int32 MaxPistolBullet = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		int32 CurPistolBullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		int32 MaxShotgunBullet = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		int32 CurShotgunBullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		int32 MaxUziBullet = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		int32 CurUziBullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		int32 MaxUziBulletLeft = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		int32 CurUziBulletLeft;

	FTimerHandle fireTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		FVector pistolFirePos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		FVector shotgunFirePos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		FVector uziFirePos;


	
	


};
