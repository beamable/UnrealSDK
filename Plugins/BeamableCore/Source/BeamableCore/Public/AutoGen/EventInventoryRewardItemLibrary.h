#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventInventoryRewardItem.h"

#include "EventInventoryRewardItemLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventInventoryRewardItemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Json", DisplayName="EventInventoryRewardItem To JSON String")
	static FString EventInventoryRewardItemToJsonString(const UEventInventoryRewardItem* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Make EventInventoryRewardItem", meta=(DefaultToSelf="Outer", AdvancedDisplay="Properties, Outer", NativeMakeFunc))
	static UEventInventoryRewardItem* Make(FString Id, FOptionalMapOfString Properties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Break EventInventoryRewardItem", meta=(NativeBreakFunc))
	static void Break(const UEventInventoryRewardItem* Serializable, FString& Id, FOptionalMapOfString& Properties);
};