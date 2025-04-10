#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SteamOrderInfoItem.h"

#include "SteamOrderInfoItemLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USteamOrderInfoItemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Json", DisplayName="SteamOrderInfoItem To JSON String")
	static FString SteamOrderInfoItemToJsonString(const USteamOrderInfoItem* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make SteamOrderInfoItem", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USteamOrderInfoItem* Make(int64 Vat, int64 Amount, int64 Itemid, int64 Qty, FString Itemstatus, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Break SteamOrderInfoItem", meta=(NativeBreakFunc))
	static void Break(const USteamOrderInfoItem* Serializable, int64& Vat, int64& Amount, int64& Itemid, int64& Qty, FString& Itemstatus);
};