// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CollectiblesCounter.generated.h"

class UTextBlock;
class AAtlantCharacter;

UCLASS()
class ATLANT_API UCollectiblesCounter : public UUserWidget
{
	GENERATED_BODY()
	
	void NativeConstruct() override;

	AAtlantCharacter* OwningCharacter;

	TArray<UTextBlock*> CollectibleNumberTexts;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BoxNumber;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SphereNumber;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ConeNumber;

	UFUNCTION()
	void Refresh();
};
