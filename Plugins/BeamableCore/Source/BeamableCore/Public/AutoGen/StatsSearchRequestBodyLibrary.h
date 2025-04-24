#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StatsSearchRequestBody.h"

#include "StatsSearchRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatsSearchRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Json", DisplayName="StatsSearchRequestBody To JSON String")
	static FString StatsSearchRequestBodyToJsonString(const UStatsSearchRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Make/Break", DisplayName="Make StatsSearchRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStatsSearchRequestBody* Make(FString Domain, FString Access, FString ObjectType, TArray<UStatsSearchCriteria*> Criteria, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Make/Break", DisplayName="Break StatsSearchRequestBody", meta=(NativeBreakFunc))
	static void Break(const UStatsSearchRequestBody* Serializable, FString& Domain, FString& Access, FString& ObjectType, TArray<UStatsSearchCriteria*>& Criteria);
};