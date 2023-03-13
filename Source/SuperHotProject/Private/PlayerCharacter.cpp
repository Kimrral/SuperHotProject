// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerWeapon_Pistol.h"
#include "BaseWeapon.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(GetMesh(), TEXT("FPSCamera"));
	VRCamera->bUsePawnControlRotation = true;
	VRCamera->SetFieldOfView(60.0f);
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Enhanced Input 사용처리
	auto PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		// LocalPlayer
		auto localPlayer = PC->GetLocalPlayer();
		auto subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer);
		if (subSystem)
		{
			subSystem->AddMappingContext(IMC_Default, 0);
		}
	}
		crosshairUI = CreateWidget<UUserWidget>(GetWorld(), crosshairFactory);
		noAmmoUI = CreateWidget<UUserWidget>(GetWorld(), noAmmoFactory);
		//if (isEnterUIEnd)
		//{
		//	crosshairUI->AddToViewport();
		//}

	
	//Pistol = GetWorld()->SpawnActor<APlayerWeapon_Pistol>(pistolFactory, GetMesh()->GetComponentLocation(), GetMesh()->GetComponentRotation());

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	if (bTestTime == true)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0);
	}
	else
	{
		TimeDilation = UKismetMathLibrary::SelectFloat(1.0, 0.04, IsMoving());
		Alpha = UKismetMathLibrary::SelectFloat(0.03, 0.5, IsMoving());
		auto lerp = UKismetMathLibrary::Lerp(UGameplayStatics::GetGlobalTimeDilation(GetWorld()), TimeDilation, Alpha);
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), lerp);
		if (IsMoving() == true)
		{
			UGameplayStatics::SetGlobalPitchModulation(GetWorld(), 1.0f, 0.3f);
		}
		else
		{
			UGameplayStatics::SetGlobalPitchModulation(GetWorld(), 0.00001f, 0.3f);
		}

	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto InputSystem = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (InputSystem)
	{
		//Binding
		InputSystem->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		InputSystem->BindAction(IA_Move, ETriggerEvent::Completed, this, &APlayerCharacter::MoveReleased);
		InputSystem->BindAction(IA_Look, ETriggerEvent::Triggered, this, &APlayerCharacter::Turn);
		InputSystem->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		InputSystem->BindAction(IA_Jump, ETriggerEvent::Completed, this, &APlayerCharacter::JumpEnd);
		InputSystem->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &APlayerCharacter::Fire);
		InputSystem->BindAction(IA_Fire, ETriggerEvent::Completed, this, &APlayerCharacter::FireReleased);
		InputSystem->BindAction(IA_Unequip, ETriggerEvent::Triggered, this, &APlayerCharacter::Unequip);
		InputSystem->BindAction(IA_Throw, ETriggerEvent::Triggered, this, &APlayerCharacter::Throw);
		InputSystem->BindAction(IA_Attach, ETriggerEvent::Triggered, this, &APlayerCharacter::Attach);

	}

	
}

void APlayerCharacter::Move(const FInputActionValue& Values)
{
	//UE_LOG(LogTemp, Warning, TEXT("Move"))
		// 사용자의 입력에 따라 앞 , 뒤 , 좌, 우로 이동하고 싶다.
		// 1. 사용자의 입력에 따라
	FVector2D Axis = Values.Get<FVector2D>();
	XMovement = Axis.X;
	YMovement = Axis.Y;
	AddMovementInput(GetActorForwardVector(), Axis.Y);
	AddMovementInput(GetActorRightVector(), Axis.X);
	// 2. 앞뒤좌우라는 방향이 필요
	//FVector Dir(Axis.X, Axis.Y, 0);
	// 3. 이동하고 싶다.
	// P = P0 + vt
	//FVector P0 = GetActorLocation();
	//FVector vt = Dir * moveSpeed *GetWorld()->DeltaTimeSeconds;
	//FVector P = P0 + vt;
	//SetActorLocation(P);

}

void APlayerCharacter::Turn(const FInputActionValue& Values)
{
	FVector2D Axis = Values.Get<FVector2D>();
	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(Axis.Y);
}

void APlayerCharacter::MoveReleased()
{
	XMovement = 0;
	YMovement = 0;
}



bool APlayerCharacter::IsMoving()
{
	bool isMoving = false;
	if (XMovement != 0 || YMovement != 0)
	{
		isMoving = true;
	}
	else
	{
		isMoving = false;
	}
	return isMoving;

}

void APlayerCharacter::Jump()
{
	ACharacter::Jump();
}

void APlayerCharacter::JumpEnd()
{
	ACharacter::StopJumping();
}

void APlayerCharacter::Fire()
{
	FVector fireLoc = GetMesh()->GetSocketLocation(TEXT("FireSocket"));
	FRotator fireRot = VRCamera->GetComponentRotation();
	FTransform fireTrans = UKismetMathLibrary::MakeTransform(fireLoc, fireRot);

	// if using weapon
	if (isWeaponEquipped)
	{
		// if using shotgun
		if (isUsingUzi==false&&isUsingShotgun==true)
		{
			// if using shotgun and have ammo
			if (bCanFire && CurShotgunBullet > 0)
			{
				CurShotgunBullet -= 1;
				ACharacter::PlayAnimMontage(punchMontage, 1.0f, TEXT("Fire"));
				UGameplayStatics::PlaySound2D(GetWorld(), shotgun_fire, 1, 1, 0, nullptr, nullptr, false);
				SpawnShotgunBullet();
				bCanFire = false;
				ResetFireCooldown();
			}
		// if using shotgun but have no ammo
			else if (isUsingShotgun && CurShotgunBullet <= 0)
			{	
				if (bCanFire)
				{
					bTestTime = true;
					UGameplayStatics::PlaySound2D(GetWorld(), pistolPickup, 0.5, 1, 0, nullptr, nullptr, false);
					UGameplayStatics::PlaySound2D(GetWorld(), OutOfAmmo, 1.5, 1, 0, nullptr, nullptr, true);
					noAmmoUI->AddToViewport();
					bCanFire = false;
					ResetFireCooldown();
					bTestTime = false;
				}
			}
		}
		// if using pistol
		else if(isUsingUzi == false && isUsingShotgun==false)
		{
			// if using pistol and have ammo
			if (bCanFire && CurPistolBullet > 0)
			{
				bTestTime = true;
				CurPistolBullet -= 1;
				ACharacter::PlayAnimMontage(punchMontage, 1.0f, TEXT("Fire"));
				UGameplayStatics::PlaySound2D(GetWorld(), pistol_fire, 1, 1, 0, nullptr, nullptr, false);
				//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), fireSmokeFactory, fireTrans);
				GetWorld()->SpawnActor<AActor>(BPProjectile, fireTrans);
				bCanFire = false;
				ResetFireCooldown();
				bTestTime = false;
			}
			// if using pistol but have no ammo
			else if (CurPistolBullet <= 0)
			{
				if (bCanFire)
				{
					bTestTime = true;
					UGameplayStatics::PlaySound2D(GetWorld(), pistolPickup, 0.5, 1, 0, nullptr, nullptr, false);
					UGameplayStatics::PlaySound2D(GetWorld(), OutOfAmmo, 1.5, 1, 0, nullptr, nullptr, true);
					noAmmoUI->AddToViewport();
					bCanFire = false;
					ResetFireCooldown();
					bTestTime = false;
				}


			}
		}
		// if using uzi
		else// if (isUsingUzi==true&&isUsingShotgun==false)
		{
			// if using uzi and have ammo
			if (bCanFire && CurUziBullet > 0)
			{
					GetWorld()->GetTimerManager().SetTimer(fireTimerHandle, FTimerDelegate::CreateLambda([this]()->void {
					if (CurUziBullet <= 0)
					{
						GetWorld()->GetTimerManager().ClearTimer(fireTimerHandle);
					}
						//bCanFire = true;
					FVector fireLoc = GetMesh()->GetSocketLocation(TEXT("FireSocket"));
					FRotator fireRot = VRCamera->GetComponentRotation();
					int32 randrot = FMath::RandRange(-1, 1);
					FTransform fireTrans = UKismetMathLibrary::MakeTransform(fireLoc, fireRot+FRotator(randrot, randrot, randrot));
					CurUziBullet -= 1;
					UE_LOG(LogTemp, Warning, TEXT("UziAmmo:%d"), CurUziBullet);
				UGameplayStatics::PlaySound2D(GetWorld(), pistol_fire, 1, 1, 0, nullptr, nullptr, false);
				GetWorld()->SpawnActor<AActor>(BPProjectile, fireTrans);
				//bCanFire = false;
				//ResetUziFireCooldown();
					}), 0.10, true);

			}
			// if using uzi but have no ammo
			else if (CurUziBullet <= 0)
			{
				if (bCanFire)
				{
					bTestTime = true;
					UGameplayStatics::PlaySound2D(GetWorld(), pistolPickup, 0.5, 1, 0, nullptr, nullptr, false);
					UGameplayStatics::PlaySound2D(GetWorld(), OutOfAmmo, 1.5, 1, 0, nullptr, nullptr, true);
					noAmmoUI->AddToViewport();
					bCanFire = false;
					ResetFireCooldown();
					bTestTime = false;
				}
			}

		}
	}
	// if not using weapon
	else
	{
		
		/*FHitResult HitInfo;
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitInfo, VRCamera->GetComponentLocation(), VRCamera->GetComponentLocation()+VRCamera->GetForwardVector()*1500,ECollisionChannel::ECC_Visibility, params);
		DrawDebugLine(GetWorld(), VRCamera->GetComponentLocation(), VRCamera->GetComponentLocation() + VRCamera->GetForwardVector() * 500, FColor::Red);
		if (bHit&&HitInfo.GetActor()->GetName().Contains(TEXT("BP_PlayerWeapon_Pistol")))
		{
			auto pistol = Cast<APlayerWeapon_Pistol>(HitInfo.GetActor());
			pistol->SetActorLocation(this->GetActorLocation()); 
		}*/
		auto anim = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());
		isMontagePlaying = anim->IsAnyMontagePlaying();
		if (isMontagePlaying == false)
		{
			if (bCanFire)
			{
				GetWorld()->SpawnActor<AActor>(BPPunchBoxComp, fireTrans);
				int32 randInt = FMath::RandRange(1, 3);
				FString montNum = FString::FromInt(randInt);
				FName montName = FName(*montNum);
				ACharacter::PlayAnimMontage(punchMontage, 1, montName);
			}
		}
		
	}






}

void APlayerCharacter::Unequip()
{
	if (isWeaponEquipped)
	{
		isWeaponEquipped = false;
	}
	else 
	{
		isWeaponEquipped = true;
	}


}

void APlayerCharacter::Throw()
{
	auto anim = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());
	isMontagePlaying = anim->IsAnyMontagePlaying();
	if (isMontagePlaying == false)
	{
		
		ACharacter::PlayAnimMontage(punchMontage, 1.0f, TEXT("Throw"));
		DetachPistol();
		isWeaponEquipped = false;


	}
}

void APlayerCharacter::DetachWeapon()
{
	/*bool pistolValid = UKismetSystemLibrary::IsValid(Pistol);
	if (pistolValid)
	{
		float ThrowVelocity = 1500.0f;
		AActor::K2_DetachFromActor(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld);
		
		auto impulse =  (VRCamera->GetForwardVector())* ThrowVelocity;
		auto prim = Cast<UPrimitiveComponent>(StaticClass());
		prim->AddImpulseAtLocation(FVector(500, 0, 0), (Pistol->GetWorldLocation()-FVector(0, 10, 0)));
		prim->AddImpulse(impulse, TEXT("none"), true);
	
	
	
	}

	*/
	//auto scene = Cast<USceneComponent>(GetMesh());
	//scene->USceneComponent::K2_DetachFromComponent(EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, true);
	//isWeaponEquipped = false;


}

/*void APlayerCharacter::ResetFireCooldown()
{
	FTimerHandle WaitHandle;
	float WaitTime = TimeBetweenShots; //시간을 설정하고
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{

			// 여기에 코드를 치면 된다.
			UGameplayStatics::PlaySound2D(GetWorld(), pistol_pickup, 1, 1, 0, nullptr, nullptr, false);

		}), WaitTime, false);
	FTimerHandle WaitHandle1;
	float WaitTime1 = 0.1f;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle1, FTimerDelegate::CreateLambda([&]()
		{
			bCanFire = true;

		}), WaitTime1, false);


}*/

void APlayerCharacter::Attach()
{
	//CurPistolBullet = MaxPistolBullet;
	//CurShotgunBullet = MaxShotgunBullet;
	//CurUziBullet = MaxUziBullet;
	return;
	if (isWeaponEquipped == false)
	{
		FHitResult HitInfo;
		FVector StartPos = VRCamera->GetComponentLocation();
		FVector EndPos = StartPos+VRCamera->GetForwardVector()*1500;
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);
		GetWorld()->LineTraceSingleByChannel(HitInfo, StartPos, EndPos, ECollisionChannel::ECC_Visibility, params);
		auto PistolRef = Cast<APlayerWeapon_Pistol>(HitInfo.GetActor());
		auto WeaponStartTrans = PistolRef->GetActorTransform();
		float alpha = 1.0f;
		auto newtrans = UKismetMathLibrary::TLerp(WeaponStartTrans, VRCamera->USceneComponent::K2_GetComponentToWorld(), alpha, ELerpInterpolationMode::QuatInterp);
		PistolRef->SetActorTransform(newtrans, false, nullptr, ETeleportType::None);
		auto pistolroot = PistolRef->GetRootComponent();
		pistolroot->USceneComponent::K2_AttachToComponent(GetMesh(), TEXT("Weapon_R"), EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
		PistolRef->PickUpC();
		isWeaponEquipped = true;
		UGameplayStatics::PlaySound2D(GetWorld(), pistol_pickup, 1, 1, 0, nullptr, nullptr, false);
	}




}

void APlayerCharacter::FireReleased()
{
	GetWorld()->GetTimerManager().ClearTimer(fireTimerHandle);
}