#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LocalizationRef.h"

#include "LocalizationRefLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULocalizationRefLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LocalizationRef To JSON String")
	static FString LocalizationRefToJsonString(const ULocalizationRef* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LocalizationRef", meta=(DefaultToSelf="Outer", AdvancedDisplay="DefaultValue, Outer", NativeMakeFunc))
	static ULocalizationRef* Make(bool bEmpty, FString LocalizationId, FOptionalString DefaultValue, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LocalizationRef", meta=(NativeBreakFunc))
	static void Break(const ULocalizationRef* Serializable, bool& bEmpty, FString& LocalizationId, FOptionalString& DefaultValue);
};