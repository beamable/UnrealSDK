
#pragma once

#include "CoreMinimal.h"
#include "SendReq.h"

#include "SendReqLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USendReqLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SendReq To JSON String")
	static FString SendReqToJsonString(const USendReq* Serializable, const bool Pretty);		
};