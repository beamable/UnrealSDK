
#pragma once

#include "CoreMinimal.h"
#include "PingRsp.h"

#include "PingRspLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPingRspLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PingRsp To JSON String")
	static FString PingRspToJsonString(const UPingRsp* Serializable, const bool Pretty);		
};