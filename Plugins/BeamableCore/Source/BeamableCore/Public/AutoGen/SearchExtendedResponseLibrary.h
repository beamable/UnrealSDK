#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SearchExtendedResponse.h"

#include "SearchExtendedResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USearchExtendedResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Json", DisplayName="SearchExtendedResponse To JSON String")
	static FString SearchExtendedResponseToJsonString(const USearchExtendedResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Make/Break", DisplayName="Make SearchExtendedResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Total, Outer", NativeMakeFunc))
	static USearchExtendedResponse* Make(int32 Offset, int32 Limit, TMap<FString, FMapOfString> GamerStats, FOptionalInt64 Total, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Make/Break", DisplayName="Break SearchExtendedResponse", meta=(NativeBreakFunc))
	static void Break(const USearchExtendedResponse* Serializable, int32& Offset, int32& Limit, TMap<FString, FMapOfString>& GamerStats, FOptionalInt64& Total);
};