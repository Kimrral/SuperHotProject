// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
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
	crosshairUI->AddToViewport();

	

	

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		InputSystem->BindAction(IA_Unequip, ETriggerEvent::Triggered, this, &APlayerCharacter::Unequip);
		InputSystem->BindAction(IA_Throw, ETriggerEvent::Triggered, this, &APlayerCharacter::Throw);
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
	if (isWeaponEquipped)
	{
		if (bCanFire)
		{
			ACharacter::PlayAnimMontage(punchMontage, 1.0f, TEXT("Fire"));
			UGameplayStatics::PlaySound2D(GetWorld(), pistol_fire, 1, 1, 0, nullptr, nullptr, false);

			GetWorld()->SpawnActor<AActor>(BPProjectile, fireTrans);
			bCanFire = false;
			ResetFireCooldown();
		}
	}
	else
	{
		auto anim = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());
		isMontagePlaying = anim->IsAnyMontagePlaying();
		if (isMontagePlaying == false)
		{
			if (bCanFire)
			{				
				ACharacter::PlayAnimMontage(punchMontage, 1, TEXT("ElbowPunch"));
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
	}
}


/*void APlayerCharacter::ResetFireCooldown()
{
	FTimerHandle WaitHandle;
	float WaitTime = TimeBetweenShots; //시간을 설정하고
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{

			// 여기에 코드를 치면 된다.
			UGameplayStatics::PlaySound2D(GetWorld(), pistol_pickup, 1, 1, 0, false);

		}), WaitTime, false);
	FTimerHandle WaitHandle1;
	float WaitTime1 = 0.1f;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle1, FTimerDelegate::CreateLambda([&]()
		{
			bCanFire = true;

		}), WaitTime1, false);


}*/