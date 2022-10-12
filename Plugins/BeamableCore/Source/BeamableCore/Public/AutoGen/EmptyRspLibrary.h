
#pragma once

#include "CoreMinimal.h"
#include "EmptyRsp.h"

#include "EmptyRspLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEmptyRspLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EmptyRsp To JSON String")
	static FString EmptyRspToJsonString(const UEmptyRsp* Serializable, const bool Pretty);		
};