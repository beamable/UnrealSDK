#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/StartResearchRequestArgs.h"

#include "StartResearchRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UStartResearchRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="StartResearchRequestArgs To JSON String")
	static FString StartResearchRequestArgsToJsonString(const UStartResearchRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make StartResearchRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStartResearchRequestArgs* Make(int64 ItemInstanceId, FString ItemContentId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break StartResearchRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UStartResearchRequestArgs* Serializable, int64& ItemInstanceId, FString& ItemContentId);
};