// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TargetWidget.generated.h"

class UTextBlock;
class AAtlantCharacter;
class AAtlantGameState;

UCLASS()
class ATLANT_API UTargetWidget : public UUserWidget
{
	GENERATED_BODY()

	void NativeConstruct() override;

	void SetupWidget();

	AAtlantCharacter* OwningCharacter;

	AAtlantGameState* GameState;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* VictoryCollectibleType;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* VictoryCollectibleAmmount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerCollectibleAmmount;

	UFUNCTION()
	void Refresh();
};
