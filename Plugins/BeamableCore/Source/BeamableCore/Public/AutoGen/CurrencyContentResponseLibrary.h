#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CurrencyContentResponse.h"

#include "CurrencyContentResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCurrencyContentResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|4 - Json", DisplayName="CurrencyContentResponse To JSON String")
	static FString CurrencyContentResponseToJsonString(const UCurrencyContentResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|3 - Backend", DisplayName="Make CurrencyContentResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCurrencyContentResponse* Make(TArray<UCurrencyArchetype*> Content, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|3 - Backend", DisplayName="Break CurrencyContentResponse", meta=(NativeBreakFunc))
	static void Break(const UCurrencyContentResponse* Serializable, TArray<UCurrencyArchetype*>& Content);
};