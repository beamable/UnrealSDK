
#pragma once

#include "CoreMinimal.h"
#include "GetCatalogReq.h"

#include "GetCatalogReqLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCatalogReqLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetCatalogReq To JSON String")
	static FString GetCatalogReqToJsonString(const UGetCatalogReq* Serializable, const bool Pretty);		
};