
#pragma once

#include "CoreMinimal.h"
#include "DonationEntry.h"

#include "DonationEntryLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UDonationEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize DonationEntry To JSON String")
	static FString DonationEntryToJsonString(const UDonationEntry* Serializable, const bool Pretty);		
};