#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetLogsUrlHeader.h"

#include "GetLogsUrlHeaderLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetLogsUrlHeaderLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="GetLogsUrlHeader To JSON String")
	static FString GetLogsUrlHeaderToJsonString(const UGetLogsUrlHeader* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make GetLogsUrlHeader", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetLogsUrlHeader* Make(FString Key, FString Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break GetLogsUrlHeader", meta=(NativeBreakFunc))
	static void Break(const UGetLogsUrlHeader* Serializable, FString& Key, FString& Value);
};