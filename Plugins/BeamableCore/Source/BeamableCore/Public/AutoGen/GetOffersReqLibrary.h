
#pragma once

#include "CoreMinimal.h"
#include "GetOffersReq.h"

#include "GetOffersReqLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetOffersReqLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetOffersReq To JSON String")
	static FString GetOffersReqToJsonString(const UGetOffersReq* Serializable, const bool Pretty);		
};