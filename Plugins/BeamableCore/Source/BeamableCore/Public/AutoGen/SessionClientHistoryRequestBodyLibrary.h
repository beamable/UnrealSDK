#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SessionClientHistoryRequestBody.h"

#include "SessionClientHistoryRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USessionClientHistoryRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|4 - Json", DisplayName="SessionClientHistoryRequestBody To JSON String")
	static FString SessionClientHistoryRequestBodyToJsonString(const USessionClientHistoryRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|3 - Backend", DisplayName="Make SessionClientHistoryRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Month, Year, Outer", NativeMakeFunc))
	static USessionClientHistoryRequestBody* Make(FOptionalInt32 Month, FOptionalInt32 Year, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|3 - Backend", DisplayName="Break SessionClientHistoryRequestBody", meta=(NativeBreakFunc))
	static void Break(const USessionClientHistoryRequestBody* Serializable, FOptionalInt32& Month, FOptionalInt32& Year);
};