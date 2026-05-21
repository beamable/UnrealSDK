#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectGroundItemRequestArgs.h"

#include "CollectGroundItemRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UCollectGroundItemRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="CollectGroundItemRequestArgs To JSON String")
	static FString CollectGroundItemRequestArgsToJsonString(const UCollectGroundItemRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make CollectGroundItemRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCollectGroundItemRequestArgs* Make(FString GroundItemId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break CollectGroundItemRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UCollectGroundItemRequestArgs* Serializable, FString& GroundItemId);
};