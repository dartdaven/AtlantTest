// Copyright Epic Games, Inc. All Rights Reserved.

#include "AtlantGameMode.h"
#include "AtlantCharacter.h"
#include "AtlantGameState.h"
#include "Kismet/GameplayStatics.h"
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
	RestartDelay = 3;
}


void AAtlantGameMode::BeginPlay()
{
	Super::BeginPlay();

	AtlantGameState = Cast<AAtlantGameState>(GameState);

	RandomizeVictoryCollectibleType();

	StartSessionTimer();

	SetupGameState();
}

void AAtlantGameMode::PlayerWon()
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PlayerController = Iterator->Get();
		AAtlantCharacter* AtlantCharacter = Cast<AAtlantCharacter>(PlayerController->GetPawn());

		if (IsValid(PlayerController) && IsValid(AtlantCharacter))
		{
			if (AtlantCharacter->GetCollectiblesCounter()[static_cast<uint8>(AtlantGameState->VictoryCollectibleType)] == AtlantGameState->VictoryCollectibleAmount)
			{
				AtlantCharacter->ShowEndSessionMessage(true);
			}
			else
			{
				AtlantCharacter->ShowEndSessionMessage(false);
			}
		}
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_SessionTimer, this, &AAtlantGameMode::RestartGame, RestartDelay);
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
	else Help::DisplayErrorMessage(TEXT("Not suitable Game State for this Game Mode"));
}

void AAtlantGameMode::StartSessionTimer()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_SessionTimer, this, &AAtlantGameMode::OnSessionTimerEnd, SessionDuration);
}

void AAtlantGameMode::OnSessionTimerEnd()
{

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PlayerController = Iterator->Get();
		AAtlantCharacter* AtlantCharacter = Cast<AAtlantCharacter>(PlayerController->GetPawn());

		if (IsValid(PlayerController) && IsValid(AtlantCharacter))
		{
			AtlantCharacter->ShowEndSessionMessage(false);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_SessionTimer, this, &AAtlantGameMode::RestartGame, RestartDelay);
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

void AAtlantGameMode::RestartGame()
{
	GetWorld()->ServerTravel("?Restart", false);
}