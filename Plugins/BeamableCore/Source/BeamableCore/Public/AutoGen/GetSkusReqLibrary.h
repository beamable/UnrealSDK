
#pragma once

#include "CoreMinimal.h"
#include "GetSkusReq.h"

#include "GetSkusReqLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetSkusReqLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetSkusReq To JSON String")
	static FString GetSkusReqToJsonString(const UGetSkusReq* Serializable, const bool Pretty);		
};