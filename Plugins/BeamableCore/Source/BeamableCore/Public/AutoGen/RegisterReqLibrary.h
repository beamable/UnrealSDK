
#pragma once

#include "CoreMinimal.h"
#include "RegisterReq.h"

#include "RegisterReqLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URegisterReqLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RegisterReq To JSON String")
	static FString RegisterReqToJsonString(const URegisterReq* Serializable, const bool Pretty);		
};