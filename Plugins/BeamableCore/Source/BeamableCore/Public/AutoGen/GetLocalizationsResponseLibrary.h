#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetLocalizationsResponse.h"

#include "GetLocalizationsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetLocalizationsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetLocalizationsResponse To JSON String")
	static FString GetLocalizationsResponseToJsonString(const UGetLocalizationsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetLocalizationsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetLocalizationsResponse* Make(TMap<FString, FArrayOfLocalizedValue> Localizations, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetLocalizationsResponse", meta=(NativeBreakFunc))
	static void Break(const UGetLocalizationsResponse* Serializable, TMap<FString, FArrayOfLocalizedValue>& Localizations);
};