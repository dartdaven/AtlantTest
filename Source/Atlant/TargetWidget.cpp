#include "TargetWidget.h"

#include "AtlantCharacter.h"
#include "AtlantGameState.h"
#include "Collectible.h"
#include "Components/TextBlock.h"
#include "HelpingTools.h"

void UTargetWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetupWidget();
}

void UTargetWidget::SetupWidget()
{
	OwningCharacter = Cast<AAtlantCharacter>(GetOwningPlayerPawn());
	GameState = GetWorld()->GetGameState<AAtlantGameState>();

	if (!IsValid(OwningCharacter) || !IsValid(GameState))
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UTargetWidget::SetupWidget);
	}
	else
	{
		OwningCharacter->OnCollectiblesCounterChange.AddDynamic(this, &UTargetWidget::Refresh);
		GameState->OnGameStateValuesChange.AddDynamic(this, &UTargetWidget::Refresh);

		Refresh();
	}
}

void UTargetWidget::Refresh()
{
	if (IsValid(OwningCharacter) && IsValid(GameState))
	{
		VictoryCollectibleType->SetText(FText::FromString(Help::EnumToString(GameState->GetVictoryCollectibleType())));
		VictoryCollectibleAmmount->SetText(FText::AsNumber(GameState->GetVictoryCollectibleAmount()));
		PlayerCollectibleAmmount->SetText(FText::AsNumber(OwningCharacter->GetCollectiblesCounter()[static_cast<uint8>(GameState->GetVictoryCollectibleType())]));
	}
}

