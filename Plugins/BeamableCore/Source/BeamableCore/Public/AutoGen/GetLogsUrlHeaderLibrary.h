#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetLogsUrlHeader.h"

#include "GetLogsUrlHeaderLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetLogsUrlHeaderLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="GetLogsUrlHeader To JSON String")
	static FString GetLogsUrlHeaderToJsonString(const UGetLogsUrlHeader* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make GetLogsUrlHeader", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetLogsUrlHeader* Make(FString Key, FString Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break GetLogsUrlHeader", meta=(NativeBreakFunc))
	static void Break(const UGetLogsUrlHeader* Serializable, FString& Key, FString& Value);
};