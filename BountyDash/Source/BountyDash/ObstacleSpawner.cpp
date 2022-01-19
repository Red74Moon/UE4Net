// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"
#include "Floor.h"
#include "Obstacle.h"
#include "BountyDashGameMode.h"
#include "BountyDash.h"
#include "EngineUtils.h"

// Sets default values
AObstacleSpawner::AObstacleSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("Root"));
	check(Scene);
	RootComponent = Scene;

	spawnTimer = 1.5f;
}

// Called when the game starts or when spawned
void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ATargetPoint> TargetIter(GetWorld()); TargetIter; ++TargetIter)
	{
		SpawnTargets.Add(*TargetIter);
	}
	for (TActorIterator<AFloor> FloorIter(GetWorld()); FloorIter; ++FloorIter)
	{
		if (FloorIter->GetWorld() == GetWorld())
		{
			KillPoint = FloorIter->GetKillPoint();
			SpawnPoint = FloorIter->GetSpawnPoint();
		}
	}
	timeSinceLastSpawn = spawnTimer;
	
}

// Called every frame
void AObstacleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timeSinceLastSpawn += DeltaTime;

	float trueSpawnTime = spawnTimer / (float)GetCustomGameMode<ABountyDashGameMode>(GetWorld())->GetGameLevel();

	if (timeSinceLastSpawn > trueSpawnTime)
	{
		timeSinceLastSpawn = 0.0f;
		SpawnObstacle();
	}
}

void AObstacleSpawner::SpawnObstacle()
{
	if (SpawnTargets.Num() > 0 && ObstataclesToSpawn.Num() > 0)
	{
		short Spawner = FMath::Rand() % SpawnTargets.Num();
		short ObStical = FMath::Rand() % ObstataclesToSpawn.Num();
		float CapsuleOffset = 0.0f;

		FActorSpawnParameters SpawnInfo;

		FTransform myTrans = SpawnTargets[Spawner]->GetTransform();
		myTrans.SetLocation(FVector(SpawnPoint, myTrans.GetLocation().Y, myTrans.GetLocation().Z));

		AObstacle* newObs = GetWorld()->SpawnActor<AObstacle>(ObstataclesToSpawn[ObStical], myTrans, SpawnInfo);

		if (newObs)
		{
			newObs->SetKillPoint(KillPoint);

			USphereComponent* obsSphere = Cast<USphereComponent>(newObs->GetComponentByClass(USphereComponent::StaticClass()));

			if (obsSphere)
			{
				newObs->AddActorLocalOffset(FVector(0.0f, 0.0f, obsSphere->GetUnscaledSphereRadius()));
			}
		}
	}

	
}

