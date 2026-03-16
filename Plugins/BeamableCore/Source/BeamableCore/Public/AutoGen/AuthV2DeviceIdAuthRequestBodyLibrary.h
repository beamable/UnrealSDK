#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2DeviceIdAuthRequestBody.h"

#include "AuthV2DeviceIdAuthRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2DeviceIdAuthRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2DeviceIdAuthRequestBody To JSON String")
	static FString AuthV2DeviceIdAuthRequestBodyToJsonString(const UAuthV2DeviceIdAuthRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2DeviceIdAuthRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="DeviceId, Scope, CustomerId, RealmId, Context, Outer", NativeMakeFunc))
	static UAuthV2DeviceIdAuthRequestBody* Make(FOptionalString DeviceId, FOptionalString Scope, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalAuthV2ContextInfo Context, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2DeviceIdAuthRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAuthV2DeviceIdAuthRequestBody* Serializable, FOptionalString& DeviceId, FOptionalString& Scope, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalAuthV2ContextInfo& Context);
};