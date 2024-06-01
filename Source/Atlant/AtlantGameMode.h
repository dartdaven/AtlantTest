// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AtlantGameMode.generated.h"

class AAtlantGameState;

UCLASS(minimalapi)
class AAtlantGameMode : public AGameModeBase
{
	GENERATED_BODY()


	TObjectPtr<AAtlantGameState> AtlantGameState;

	FTimerHandle TimerHandle_SessionTimer;

	/* Time in seconds representing one game session duration */
	UPROPERTY(EditDefaultsOnly, Category = Rules)
	float SessionDuration;

	/* Amount of certain collectible needed to win the session */
	UPROPERTY(EditDefaultsOnly, Category = Rules, meta = (AllowPrivateAccess = "true")) //BUG Is not overridden by Blueprint Defaults
	uint64 VictoryCollectibleAmount;

	void RandomizeVictoryCollectibleType();

	void SetupGameState();

	void StartSessionTimer();

	void OnSessionTimerEnd();

public:
	AAtlantGameMode();

	void BeginPlay() override;
};



