// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "Collectible.h"

#include "AtlantGameState.generated.h"

UCLASS()
class ATLANT_API AAtlantGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	ECollectibleType VictoryCollectibleType;

	uint64 VictoryCollectibleAmount;

public:
	AAtlantGameState();

	ECollectibleType GetVictoryCollectibleType() const { return VictoryCollectibleType; }
	uint64 GetVictoryCollectibleAmount() const { return VictoryCollectibleAmount; }

	
};
