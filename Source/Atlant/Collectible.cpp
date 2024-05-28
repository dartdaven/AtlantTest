#include "Collectible.h"

#include "Math/UnrealMathUtility.h"
#include "Net/UnrealNetwork.h"

#include "HelpingTools.h"

// Sets default values
ACollectible::ACollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	bAlwaysRelevant = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
	//For outline to work
	Mesh->CustomDepthStencilValue = 1;

}

// Called when the game starts or when spawned
void ACollectible::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority()) RandomizeType();
}

void ACollectible::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (!HasAuthority()) UpdateMesh();
}

void ACollectible::RandomizeType_Implementation()
{
	const uint8 EnumRange = static_cast<uint8>(ECollectibleType::End);

	uint8 RandomValue = FMath::RandRange(0, EnumRange - 1);
	
	CollectibleType = static_cast<ECollectibleType>(RandomValue);

	UpdateMesh();
}

void ACollectible::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACollectible, CollectibleType);
}

void ACollectible::OnRep_CollectibleType()
{
	UpdateMesh();
}

void ACollectible::UpdateMesh()
{
	if (CollectibleType == ECollectibleType::Box)
	{
		if (IsValid(BoxMesh))
		{
			Mesh->SetStaticMesh(BoxMesh);
		}
		else
		{
			Help::DisplayErrorMessage(TEXT("%s: There is no Box mesh for Box type"), *GetNameSafe(this));
		}
	}
	else if (CollectibleType == ECollectibleType::Sphere)
	{
		if (IsValid(SphereMesh))
		{
			Mesh->SetStaticMesh(SphereMesh);
		}
		else
		{
			Help::DisplayErrorMessage(TEXT("%s: There is no Sohere mesh for Sphere type"), *GetNameSafe(this));
		}
	}
	else if (CollectibleType == ECollectibleType::Cone)
	{
		if (IsValid(ConeMesh))
		{
			Mesh->SetStaticMesh(ConeMesh);
		}
		else
		{
			Help::DisplayErrorMessage(TEXT("%s: There is no Cone mesh for Cone type"), *GetNameSafe(this));
		}
	}
	else
	{
		Help::DisplayErrorMessage(TEXT("%s: Not known collectible type is selected"), *GetNameSafe(this));
	}
}
