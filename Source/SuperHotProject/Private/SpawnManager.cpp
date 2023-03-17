// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"
#include "Enemy.h"
#include "VRGameModeBase.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(timerHandleSpawnEnemy, this, &ASpawnManager::SpawnEnemy, spawnTime, false);

}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnManager::SpawnEnemy()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawn Enemy"));
	GetWorld()->SpawnActor<AEnemy>(enemyFactory, GetActorLocation(), GetActorRotation());
	AVRGameModeBase* myMode = Cast<AVRGameModeBase>(GetWorld()->GetAuthGameMode());
	if (myMode) {
		if (!myMode->bSpawn) {
			myMode->bSpawn = true;
		}
		myMode->totalEnemy++;
	}
}

