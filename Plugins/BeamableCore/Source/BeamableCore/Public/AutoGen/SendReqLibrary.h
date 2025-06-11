#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SendReq.h"

#include "SendReqLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USendReqLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Push|Utils|Json", DisplayName="SendReq To JSON String")
	static FString SendReqToJsonString(const USendReq* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Push|Utils|Make/Break", DisplayName="Make SendReq", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USendReq* Make(TArray<USendMsg*> Msgs, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Push|Utils|Make/Break", DisplayName="Break SendReq", meta=(NativeBreakFunc))
	static void Break(const USendReq* Serializable, TArray<USendMsg*>& Msgs);
};