
#pragma once

#include "CoreMinimal.h"
#include "EventQueryResponse.h"

#include "EventQueryResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventQueryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventQueryResponse To JSON String")
	static FString EventQueryResponseToJsonString(const UEventQueryResponse* Serializable, const bool Pretty);		
};