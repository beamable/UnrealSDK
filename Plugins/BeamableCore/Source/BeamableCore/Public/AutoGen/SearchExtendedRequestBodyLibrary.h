#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SearchExtendedRequestBody.h"

#include "SearchExtendedRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USearchExtendedRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="SearchExtendedRequestBody To JSON String")
	static FString SearchExtendedRequestBodyToJsonString(const USearchExtendedRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make SearchExtendedRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USearchExtendedRequestBody* Make(FString Domain, FString ObjectType, FString Access, TArray<UStatsSearchCriteria*> Criteria, TArray<FString> StatKeys, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break SearchExtendedRequestBody", meta=(NativeBreakFunc))
	static void Break(const USearchExtendedRequestBody* Serializable, FString& Domain, FString& ObjectType, FString& Access, TArray<UStatsSearchCriteria*>& Criteria, TArray<FString>& StatKeys);
};