// Fill out your copyright notice in the Description page of Project Settings.


#include "AtlantGameState.h"

#include "Net/UnrealNetwork.h"

AAtlantGameState::AAtlantGameState()
{
}

void AAtlantGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAtlantGameState, VictoryCollectibleType);
	DOREPLIFETIME(AAtlantGameState, VictoryCollectibleAmount);
	DOREPLIFETIME(AAtlantGameState, SessionEndTime);
}
