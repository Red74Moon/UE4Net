// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "Coin.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYDASH_API ACoin : public AObstacle
{
	GENERATED_BODY()

public:
	ACoin();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void MyOnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	
};
