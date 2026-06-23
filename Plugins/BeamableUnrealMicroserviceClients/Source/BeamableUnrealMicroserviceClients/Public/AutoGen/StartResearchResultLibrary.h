#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/StartResearchResult.h"

#include "StartResearchResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UStartResearchResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="StartResearchResult To JSON String")
	static FString StartResearchResultToJsonString(const UStartResearchResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make StartResearchResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStartResearchResult* Make(int64 StartedAtUtcSeconds, int32 PointsSpent, FString Message, bool bSuccess, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break StartResearchResult", meta=(NativeBreakFunc))
	static void Break(const UStartResearchResult* Serializable, int64& StartedAtUtcSeconds, int32& PointsSpent, FString& Message, bool& bSuccess);
};