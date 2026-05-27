#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectResearchResult.h"

#include "CollectResearchResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UCollectResearchResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="CollectResearchResult To JSON String")
	static FString CollectResearchResultToJsonString(const UCollectResearchResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make CollectResearchResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCollectResearchResult* Make(FString OutputContentId, int32 OutputQuantity, FString OutputType, FString Message, bool bSuccess, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break CollectResearchResult", meta=(NativeBreakFunc))
	static void Break(const UCollectResearchResult* Serializable, FString& OutputContentId, int32& OutputQuantity, FString& OutputType, FString& Message, bool& bSuccess);
};