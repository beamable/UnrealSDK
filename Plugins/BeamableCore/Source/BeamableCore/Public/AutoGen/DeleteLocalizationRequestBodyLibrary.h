#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DeleteLocalizationRequestBody.h"

#include "DeleteLocalizationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDeleteLocalizationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="DeleteLocalizationRequestBody To JSON String")
	static FString DeleteLocalizationRequestBodyToJsonString(const UDeleteLocalizationRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make DeleteLocalizationRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDeleteLocalizationRequestBody* Make(TArray<ULocalizationQuery*> Localizations, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break DeleteLocalizationRequestBody", meta=(NativeBreakFunc))
	static void Break(const UDeleteLocalizationRequestBody* Serializable, TArray<ULocalizationQuery*>& Localizations);
};