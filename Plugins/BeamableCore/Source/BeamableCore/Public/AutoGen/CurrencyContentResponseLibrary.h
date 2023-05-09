#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CurrencyContentResponse.h"

#include "CurrencyContentResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCurrencyContentResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CurrencyContentResponse To JSON String")
	static FString CurrencyContentResponseToJsonString(const UCurrencyContentResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CurrencyContentResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCurrencyContentResponse* Make(TArray<UCurrencyArchetype*> Content, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break CurrencyContentResponse", meta=(NativeBreakFunc))
	static void Break(const UCurrencyContentResponse* Serializable, TArray<UCurrencyArchetype*>& Content);
};