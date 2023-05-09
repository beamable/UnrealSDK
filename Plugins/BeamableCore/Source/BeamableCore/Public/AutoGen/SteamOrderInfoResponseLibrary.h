#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SteamOrderInfoResponse.h"

#include "SteamOrderInfoResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USteamOrderInfoResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - SteamOrderInfoResponse To JSON String")
	static FString SteamOrderInfoResponseToJsonString(const USteamOrderInfoResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make SteamOrderInfoResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USteamOrderInfoResponse* Make(FString Usstate, FString Country, FString Timecreated, int64 Transid, FString Status, int64 Orderid, int64 Steamid, FString Currency, FString Time, TArray<USteamOrderInfoItem*> Items, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break SteamOrderInfoResponse", meta=(NativeBreakFunc))
	static void Break(const USteamOrderInfoResponse* Serializable, FString& Usstate, FString& Country, FString& Timecreated, int64& Transid, FString& Status, int64& Orderid, int64& Steamid, FString& Currency, FString& Time, TArray<USteamOrderInfoItem*>& Items);
};