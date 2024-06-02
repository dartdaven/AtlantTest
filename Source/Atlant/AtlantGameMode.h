// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AtlantGameMode.generated.h"

class AAtlantGameState;
class AAtlantCharacter;

UCLASS(minimalapi)
class AAtlantGameMode : public AGameModeBase
{
	GENERATED_BODY()

	TObjectPtr<AAtlantGameState> AtlantGameState;

	FTimerHandle TimerHandle_SessionTimer;

	/* Time in seconds representing one game session duration */
	UPROPERTY(EditDefaultsOnly, Category = Rules)
	float SessionDuration;

	/* Time in seconds between game session ends and a new session starts 
	Also note that RestartGame() method has it's own delay time*/
	UPROPERTY(EditDefaultsOnly, Category = Rules)
	uint8 RestartDelay;

	/* Amount of certain collectible needed to win the session */
	UPROPERTY(EditDefaultsOnly, Category = Rules) //BUG Is not overridden by Blueprint Defaults
	uint64 VictoryCollectibleAmount;

	void RandomizeVictoryCollectibleType();

	void SetupGameState();

	void StartSessionTimer();

	void OnSessionTimerEnd();

	void RestartGame();

public:
	AAtlantGameMode();

	void BeginPlay() override;

	void PlayerWon();
};



