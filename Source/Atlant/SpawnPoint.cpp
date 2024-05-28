#include "SpawnPoint.h"

#include "Net/UnrealNetwork.h"

#include "Collectible.h"
#include "HelpingTools.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	bAlwaysRelevant = true;

	SpawnedCollectible = nullptr;

	MinTimeRange = 10.f;
	MaxTimeRange = 40.f;
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	if(HasAuthority()) SetRandomTimer();
}

void ASpawnPoint::SetRandomTimer()
{
	float RandomTime = FMath::RandRange(MinTimeRange, MaxTimeRange);

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnPoint::SpawnCollectible, RandomTime, false);
}

void ASpawnPoint::SpawnCollectible()
{

	if (!HasAuthority()) return;

	if (IsValid(SpawnedCollectible))
	{
		SpawnedCollectible->Destroy();
	}

	if (IsValid(CollectibleClass))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		FTransform SpawnTransform = GetActorTransform();

		SpawnedCollectible = GetWorld()->SpawnActor<ACollectible>(CollectibleClass, SpawnTransform, SpawnParams);

		SetRandomTimer();
	}
	else Help::DisplayErrorMessage(TEXT("Collectible Class in SpawnPoint is not valid"));
}


void ASpawnPoint::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASpawnPoint, SpawnedCollectible);
}
