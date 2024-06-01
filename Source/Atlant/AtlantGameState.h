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
	
	friend class AAtlantGameMode;

	UPROPERTY(Replicated)
	ECollectibleType VictoryCollectibleType;

	UPROPERTY(Replicated)
	uint64 VictoryCollectibleAmount;

	UPROPERTY(Replicated)
	float SessionEndTime;


public:
	AAtlantGameState();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStateValuesChange);
	FOnGameStateValuesChange OnGameStateValuesChange;

	ECollectibleType GetVictoryCollectibleType() const { return VictoryCollectibleType; }
	uint64 GetVictoryCollectibleAmount() const { return VictoryCollectibleAmount; }

	UFUNCTION(BlueprintCallable)
	float GetSessionEndTime() const { return SessionEndTime; }

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
};
