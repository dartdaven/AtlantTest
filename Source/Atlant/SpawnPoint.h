// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

class ACollectible;

UCLASS()
class ATLANT_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(Replicated)
	ACollectible* SpawnedCollectible;

	FTimerHandle SpawnTimerHandle;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	TSubclassOf<ACollectible> CollectibleClass;

	/* Lower border in seconds of time range for spawn point to randomize time */
	UPROPERTY(EditAnywhere, Category = Gameplay, meta = (AllowPrivateAccess = "true", ClampMin = "0"))
	float MinTimeRange;

	/* Should be higher than MinTimeRange */
	UPROPERTY(EditAnywhere, Category = Gameplay, meta = (AllowPrivateAccess = "true", ClampMin = "0"))
	float MaxTimeRange;

	UFUNCTION()
	void SpawnCollectible();

	void SetRandomTimer();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	ASpawnPoint();

protected:
	virtual void BeginPlay() override;

};
