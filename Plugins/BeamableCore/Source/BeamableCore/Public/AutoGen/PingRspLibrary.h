#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PingRsp.h"

#include "PingRspLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPingRspLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Json", DisplayName="PingRsp To JSON String")
	static FString PingRspToJsonString(const UPingRsp* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Make PingRsp", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPingRsp* Make(bool bKeepAlive, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Break PingRsp", meta=(NativeBreakFunc))
	static void Break(const UPingRsp* Serializable, bool& bKeepAlive);
};