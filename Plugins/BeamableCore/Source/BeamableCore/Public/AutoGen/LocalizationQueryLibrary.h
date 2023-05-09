#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LocalizationQuery.h"

#include "LocalizationQueryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULocalizationQueryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LocalizationQuery To JSON String")
	static FString LocalizationQueryToJsonString(const ULocalizationQuery* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LocalizationQuery", meta=(DefaultToSelf="Outer", AdvancedDisplay="Languages, Outer", NativeMakeFunc))
	static ULocalizationQuery* Make(FString Id, FOptionalArrayOfString Languages, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LocalizationQuery", meta=(NativeBreakFunc))
	static void Break(const ULocalizationQuery* Serializable, FString& Id, FOptionalArrayOfString& Languages);
};