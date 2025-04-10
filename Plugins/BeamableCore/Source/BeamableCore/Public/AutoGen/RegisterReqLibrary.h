#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RegisterReq.h"

#include "RegisterReqLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URegisterReqLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Push|4 - Json", DisplayName="RegisterReq To JSON String")
	static FString RegisterReqToJsonString(const URegisterReq* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Push|3 - Backend", DisplayName="Make RegisterReq", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URegisterReq* Make(FString Provider, FString Token, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Push|3 - Backend", DisplayName="Break RegisterReq", meta=(NativeBreakFunc))
	static void Break(const URegisterReq* Serializable, FString& Provider, FString& Token);
};