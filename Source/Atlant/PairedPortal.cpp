#include "PairedPortal.h"

#include "HelpingTools.h"

// Sets default values
APairedPortal::APairedPortal()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APairedPortal::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(PairedPortal))
	{
		APairedPortal* OtherPortalsPointer = PairedPortal->PairedPortal;

		if (!OtherPortalsPointer)
		{
			//TODO they are created not simulteneously 
			OtherPortalsPointer = this;
		}
		else if (OtherPortalsPointer != this)
		{
			Help::DisplayErrorMessage(TEXT("%s: Portals are not set up properly"), *GetNameSafe(this));
		}
	}
	else Help::DisplayDebugMessage(TEXT("%s: Please set the pair for the teleport to function"), *GetNameSafe(this));
}