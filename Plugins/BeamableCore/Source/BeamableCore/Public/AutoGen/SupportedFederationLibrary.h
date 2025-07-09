#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SupportedFederation.h"

#include "SupportedFederationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USupportedFederationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="SupportedFederation To JSON String")
	static FString SupportedFederationToJsonString(const USupportedFederation* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make SupportedFederation", meta=(DefaultToSelf="Outer", AdvancedDisplay="Type, NameSpace, Outer", NativeMakeFunc))
	static USupportedFederation* Make(FOptionalFederationType Type, FOptionalString NameSpace, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break SupportedFederation", meta=(NativeBreakFunc))
	static void Break(const USupportedFederation* Serializable, FOptionalFederationType& Type, FOptionalString& NameSpace);
};