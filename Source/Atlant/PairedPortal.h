// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HelpingTools.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PairedPortal.generated.h"

UCLASS()
class ATLANT_API APairedPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APairedPortal();

	UPROPERTY (EditInstanceOnly, BlueprintReadOnly, Category = "Gameplay")
	APairedPortal* PairedPortal;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
