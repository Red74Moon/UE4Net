// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BountyDashGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYDASH_API ABountyDashGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ABountyDashGameMode();

public:
	UPROPERTY()
		float gameSpeed;
	UPROPERTY()
		int32 gameLevel;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 numCoinsForSpeedIncrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float gameSpeedIncrease;

public:
	void CharScoreUp(unsigned int charScore);

	UFUNCTION()
		float GetInvGameSpeed();

	UFUNCTION()
		float GetGameSpeed();

	UFUNCTION()
		int32 GetGameLevel();
};
