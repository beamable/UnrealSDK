#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetStoresReq.h"

#include "GetStoresReqLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetStoresReqLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="GetStoresReq To JSON String")
	static FString GetStoresReqToJsonString(const UGetStoresReq* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make GetStoresReq", meta=(DefaultToSelf="Outer", AdvancedDisplay="Scope, Outer", NativeMakeFunc))
	static UGetStoresReq* Make(FOptionalString Scope, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break GetStoresReq", meta=(NativeBreakFunc))
	static void Break(const UGetStoresReq* Serializable, FOptionalString& Scope);
};