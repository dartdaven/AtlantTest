// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectiblesCounter.h"

#include "AtlantCharacter.h"
#include "Components/TextBlock.h"
#include "HelpingTools.h"

void UCollectiblesCounter::NativeConstruct()
{
	Super::NativeConstruct();

	OwningCharacter = Cast<AAtlantCharacter>(GetOwningPlayerPawn());

	if (IsValid(OwningCharacter)) OwningCharacter->OnCollectiblesCounterChange.AddDynamic(this, &UCollectiblesCounter::Refresh);

	//Hardcode warning
	//Order is inavitable
	CollectibleNumberTexts.Add(BoxNumber);
	CollectibleNumberTexts.Add(SphereNumber);
	CollectibleNumberTexts.Add(ConeNumber);

	Refresh();
}

void UCollectiblesCounter::Refresh()
{
	if(IsValid(OwningCharacter))
	{
		TArray<uint64> PlayersCounter = OwningCharacter->GetCollectiblesCounter();

		if (PlayersCounter.Num() == CollectibleNumberTexts.Num())
		{
			for (int i = 0; i < CollectibleNumberTexts.Num(); i++)
			{
				CollectibleNumberTexts[i]->SetText(FText::AsNumber(PlayersCounter[i]));
			}
		}
		else Help::DisplayErrorMessage(TEXT("Widget collectibles does not match with real collectibles"));
	}
}
