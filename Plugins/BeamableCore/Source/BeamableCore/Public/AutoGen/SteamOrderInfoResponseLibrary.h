#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SteamOrderInfoResponse.h"

#include "SteamOrderInfoResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USteamOrderInfoResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Json", DisplayName="SteamOrderInfoResponse To JSON String")
	static FString SteamOrderInfoResponseToJsonString(const USteamOrderInfoResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make SteamOrderInfoResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USteamOrderInfoResponse* Make(FString Usstate, FString Country, FString Timecreated, int64 Transid, FString Status, int64 Orderid, int64 Steamid, FString Currency, FString Time, TArray<USteamOrderInfoItem*> Items, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Break SteamOrderInfoResponse", meta=(NativeBreakFunc))
	static void Break(const USteamOrderInfoResponse* Serializable, FString& Usstate, FString& Country, FString& Timecreated, int64& Transid, FString& Status, int64& Orderid, int64& Steamid, FString& Currency, FString& Time, TArray<USteamOrderInfoItem*>& Items);
};