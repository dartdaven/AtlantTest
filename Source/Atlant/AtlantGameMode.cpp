// Copyright Epic Games, Inc. All Rights Reserved.

#include "AtlantGameMode.h"
#include "AtlantCharacter.h"
#include "AtlantGameState.h"
#include "UObject/ConstructorHelpers.h"

AAtlantGameMode::AAtlantGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	GameStateClass = AAtlantGameState::StaticClass();
}
