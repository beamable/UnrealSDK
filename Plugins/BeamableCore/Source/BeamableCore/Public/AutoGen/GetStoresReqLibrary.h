
#pragma once

#include "CoreMinimal.h"
#include "GetStoresReq.h"

#include "GetStoresReqLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetStoresReqLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetStoresReq To JSON String")
	static FString GetStoresReqToJsonString(const UGetStoresReq* Serializable, const bool Pretty);		
};