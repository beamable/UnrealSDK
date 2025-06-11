#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SessionHistoryRequestBody.h"

#include "SessionHistoryRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USessionHistoryRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="SessionHistoryRequestBody To JSON String")
	static FString SessionHistoryRequestBodyToJsonString(const USessionHistoryRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make SessionHistoryRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Month, Year, Outer", NativeMakeFunc))
	static USessionHistoryRequestBody* Make(int64 Dbid, FOptionalInt32 Month, FOptionalInt32 Year, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Break SessionHistoryRequestBody", meta=(NativeBreakFunc))
	static void Break(const USessionHistoryRequestBody* Serializable, int64& Dbid, FOptionalInt32& Month, FOptionalInt32& Year);
};