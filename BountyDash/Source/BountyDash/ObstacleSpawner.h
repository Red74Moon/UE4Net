// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"

UCLASS()
class BOUNTYDASH_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObstacleSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	void SpawnObstacle();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<class AObstacle>> ObstataclesToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class ATargetPoint*> SpawnTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float spawnTimer;

	UPROPERTY()
		USceneComponent* Scene;

private:
	float KillPoint;
	float SpawnPoint;
	float timeSinceLastSpawn;

};