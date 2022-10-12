
#pragma once

#include "CoreMinimal.h"
#include "DataDomain.h"

#include "DataDomainLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UDataDomainLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize DataDomain To JSON String")
	static FString DataDomainToJsonString(const UDataDomain* Serializable, const bool Pretty);		
};