#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectGroundItemResult.h"

#include "CollectGroundItemResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UCollectGroundItemResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="CollectGroundItemResult To JSON String")
	static FString CollectGroundItemResultToJsonString(const UCollectGroundItemResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make CollectGroundItemResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCollectGroundItemResult* Make(FString GrantedContentId, int32 GrantedQuantity, FString Message, bool bSuccess, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break CollectGroundItemResult", meta=(NativeBreakFunc))
	static void Break(const UCollectGroundItemResult* Serializable, FString& GrantedContentId, int32& GrantedQuantity, FString& Message, bool& bSuccess);
};