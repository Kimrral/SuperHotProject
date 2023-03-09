// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerWeapon_Pistol.h"

// Called when the game starts or when spawned
 
APlayerWeapon_Pistol::APlayerWeapon_Pistol()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	traceCheckBox = CreateDefaultSubobject<UBoxComponent>(TEXT("traceCheckBox"));
	traceCheckBox->SetBoxExtent(FVector(25.f, 10.f, 15.f));
	traceCheckBox->SetupAttachment(BoxComp);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> gunMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/MilitaryWeapSilver/Weapons/Pistols_A.Pistols_A'"));
	if (gunMesh.Succeeded()) {
		MeshComp->SetSkeletalMesh(gunMesh.Object);
	}

}



void APlayerWeapon_Pistol::BeginPlay()
{
	Super::BeginPlay();


	// 충돌(오버랩)이 발생하면 실행할 함수를 연결한다.
	//BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerWeapon_Pistol::OnOverlap);

	// 오버랩 이벤트가 발생하도록 설정한다.
	//BoxComp->SetGenerateOverlapEvents(true);

}

// Called every frame
void APlayerWeapon_Pistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*void APlayerWeapon_Pistol::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	player->isWeaponEquipped = true;
	AActor::K2_AttachToComponent(player->GetMesh(), TEXT("Weapon_R"), EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);


}*/



void APlayerWeapon_Pistol::PickUpC()
{
	BoxComp->UPrimitiveComponent::SetAllPhysicsLinearVelocity(FVector::ZeroVector, false);
	BoxComp->UPrimitiveComponent::SetSimulatePhysics(false);
	BoxComp->UPrimitiveComponent::SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

