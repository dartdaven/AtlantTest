// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectible.generated.h"

UENUM(BlueprintType)
enum class ECollectibleType : uint8 //The type shouldn't be more than a byte
{
	Box,
	Sphere,
	Cone,
	End UMETA(Hidden),
};

UCLASS()
class ATLANT_API ACollectible : public AActor
{
	GENERATED_BODY()

	UPROPERTY(ReplicatedUsing = OnRep_CollectibleType)
	ECollectibleType CollectibleType;

	/* Will be automaticly chosen during Begin Play */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Appearance, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = Appearance)
	TObjectPtr<UStaticMesh> BoxMesh;

	UPROPERTY(EditDefaultsOnly, Category = Appearance)
	TObjectPtr<UStaticMesh> SphereMesh;

	UPROPERTY(EditDefaultsOnly, Category = Appearance)
	TObjectPtr<UStaticMesh> ConeMesh;

	UFUNCTION()
	void OnRep_CollectibleType();

	UFUNCTION(Server, Reliable)
	void RandomizeType();
	
	void UpdateMesh();
	
public:	
	// Sets default values for this actor's properties
	ACollectible();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE uint8 GetTypeNumber() const { return static_cast<uint8>(CollectibleType); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ECollectibleType GetType() const { return CollectibleType;  }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

};
