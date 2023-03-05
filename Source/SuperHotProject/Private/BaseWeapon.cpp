// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Projectile.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(25.f, 10.f, 15.f));
	SetRootComponent(BoxComp);

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(BoxComp);

	MeshComp->SetRelativeRotation(FRotator(0, -90, 0));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> gunMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));
	if (gunMesh.Succeeded()) {
		MeshComp->SetSkeletalMesh(gunMesh.Object);
	}

}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeapon::DoFire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire"));
	FTransform firePosition = MeshComp->GetSocketTransform(TEXT("Muzzle"));

	FRotator smokeRot = MeshComp->GetSocketRotation(TEXT("Smoke"));
	FVector smokeLoc = MeshComp->GetSocketLocation(TEXT("Smoke"));
	GetWorld()->SpawnActor<AProjectile>(bulletFactory, firePosition);

	if (NA_SmokeRing) {
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NA_SmokeRing, smokeLoc, smokeRot);
	}
}

void ABaseWeapon::FirePressed()
{
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ABaseWeapon::DoFire, FireRate, true);
	DoFire();

}

void ABaseWeapon::FireRelease()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}


