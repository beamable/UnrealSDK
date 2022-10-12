
#pragma once

#include "CoreMinimal.h"
#include "AccountPersonallyIdentifiableInformationResponse.h"

#include "AccountPersonallyIdentifiableInformationResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAccountPersonallyIdentifiableInformationResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AccountPersonallyIdentifiableInformationResponse To JSON String")
	static FString AccountPersonallyIdentifiableInformationResponseToJsonString(const UAccountPersonallyIdentifiableInformationResponse* Serializable, const bool Pretty);		
};