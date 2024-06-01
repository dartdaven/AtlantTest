// Copyright Epic Games, Inc. All Rights Reserved.

#include "AtlantGameMode.h"
#include "AtlantCharacter.h"
#include "AtlantGameState.h"
#include "UObject/ConstructorHelpers.h"

#include "HelpingTools.h"

AAtlantGameMode::AAtlantGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	GameStateClass = AAtlantGameState::StaticClass();

	SessionDuration = 120.f;
	VictoryCollectibleAmount = 5;

}


void AAtlantGameMode::BeginPlay()
{
	Super::BeginPlay();

	AtlantGameState = Cast<AAtlantGameState>(GameState);

	RandomizeVictoryCollectibleType();

	StartSessionTimer();

	SetupGameState();
}

void AAtlantGameMode::RandomizeVictoryCollectibleType()
{

	if (IsValid(AtlantGameState))
	{
		const uint8 EnumRange = static_cast<uint8>(ECollectibleType::End);
		uint8 RandomValue = FMath::RandRange(0, EnumRange - 1);

		Help::DisplayDebugMessage(TEXT("Random value in Gamemode: %d"), RandomValue);

		AtlantGameState->VictoryCollectibleType = static_cast<ECollectibleType>(RandomValue);

		AtlantGameState->OnGameStateValuesChange.Broadcast();
	}
}

void AAtlantGameMode::StartSessionTimer()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_SessionTimer, this, &AAtlantGameMode::OnSessionTimerEnd, SessionDuration);
}

void AAtlantGameMode::OnSessionTimerEnd()
{
}

void AAtlantGameMode::SetupGameState()
{
	if (IsValid(AtlantGameState))
	{
		AtlantGameState->VictoryCollectibleAmount = VictoryCollectibleAmount;

		float TimeRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(TimerHandle_SessionTimer);
		AtlantGameState->SessionEndTime = GetWorld()->GetTimeSeconds() + TimeRemaining;

		AtlantGameState->OnGameStateValuesChange.Broadcast();
	}
}