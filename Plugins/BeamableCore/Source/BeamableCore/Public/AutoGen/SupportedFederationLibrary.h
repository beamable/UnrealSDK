#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SupportedFederation.h"

#include "SupportedFederationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USupportedFederationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - SupportedFederation To JSON String")
	static FString SupportedFederationToJsonString(const USupportedFederation* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make SupportedFederation", meta=(DefaultToSelf="Outer", AdvancedDisplay="NameSpace, Settings, Outer", NativeMakeFunc))
	static USupportedFederation* Make(EFederationType Type, FOptionalString NameSpace, FOptionalOptionalJsonNodeWrapper Settings, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break SupportedFederation", meta=(NativeBreakFunc))
	static void Break(const USupportedFederation* Serializable, EFederationType& Type, FOptionalString& NameSpace, FOptionalOptionalJsonNodeWrapper& Settings);
};