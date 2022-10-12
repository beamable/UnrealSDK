
#pragma once

#include "CoreMinimal.h"
#include "ClientDataEntry.h"

#include "ClientDataEntryLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UClientDataEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ClientDataEntry To JSON String")
	static FString ClientDataEntryToJsonString(const UClientDataEntry* Serializable, const bool Pretty);		
};