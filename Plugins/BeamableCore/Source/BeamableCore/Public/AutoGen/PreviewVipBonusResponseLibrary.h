
#pragma once

#include "CoreMinimal.h"
#include "PreviewVipBonusResponse.h"

#include "PreviewVipBonusResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPreviewVipBonusResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PreviewVipBonusResponse To JSON String")
	static FString PreviewVipBonusResponseToJsonString(const UPreviewVipBonusResponse* Serializable, const bool Pretty);		
};