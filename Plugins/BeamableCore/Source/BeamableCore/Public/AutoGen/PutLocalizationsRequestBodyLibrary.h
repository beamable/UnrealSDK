#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PutLocalizationsRequestBody.h"

#include "PutLocalizationsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPutLocalizationsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - PutLocalizationsRequestBody To JSON String")
	static FString PutLocalizationsRequestBodyToJsonString(const UPutLocalizationsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make PutLocalizationsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPutLocalizationsRequestBody* Make(TMap<FString, FArrayOfLocalizedValue> Localizations, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break PutLocalizationsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UPutLocalizationsRequestBody* Serializable, TMap<FString, FArrayOfLocalizedValue>& Localizations);
};