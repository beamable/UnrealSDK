#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectResearchRequestArgs.h"

#include "CollectResearchRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UCollectResearchRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="CollectResearchRequestArgs To JSON String")
	static FString CollectResearchRequestArgsToJsonString(const UCollectResearchRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make CollectResearchRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCollectResearchRequestArgs* Make(int64 ItemInstanceId, FString ItemContentId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break CollectResearchRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UCollectResearchRequestArgs* Serializable, int64& ItemInstanceId, FString& ItemContentId);
};