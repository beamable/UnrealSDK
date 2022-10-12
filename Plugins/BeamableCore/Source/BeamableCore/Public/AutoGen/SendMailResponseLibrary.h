
#pragma once

#include "CoreMinimal.h"
#include "SendMailResponse.h"

#include "SendMailResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USendMailResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SendMailResponse To JSON String")
	static FString SendMailResponseToJsonString(const USendMailResponse* Serializable, const bool Pretty);		
};