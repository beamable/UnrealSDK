#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/GetOffersReq.h"

#include "GetOffersReqLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetOffersReqLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetOffersReq To JSON String")
	static FString GetOffersReqToJsonString(const UGetOffersReq* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetOffersReq", meta=(DefaultToSelf="Outer", AdvancedDisplay="Language, Time, Stores, Outer", NativeMakeFunc))
	static UGetOffersReq* Make(FOptionalString Language, FOptionalString Time, FOptionalString Stores, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetOffersReq", meta=(NativeBreakFunc))
	static void Break(const UGetOffersReq* Serializable, FOptionalString& Language, FOptionalString& Time, FOptionalString& Stores);
};