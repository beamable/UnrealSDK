#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LocalizationRef.h"

#include "LocalizationRefLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULocalizationRefLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Json", DisplayName="LocalizationRef To JSON String")
	static FString LocalizationRefToJsonString(const ULocalizationRef* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make LocalizationRef", meta=(DefaultToSelf="Outer", AdvancedDisplay="DefaultValue, Outer", NativeMakeFunc))
	static ULocalizationRef* Make(bool bEmpty, FString LocalizationId, FOptionalString DefaultValue, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Break LocalizationRef", meta=(NativeBreakFunc))
	static void Break(const ULocalizationRef* Serializable, bool& bEmpty, FString& LocalizationId, FOptionalString& DefaultValue);
};