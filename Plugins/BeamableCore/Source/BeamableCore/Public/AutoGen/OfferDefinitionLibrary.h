#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/OfferDefinition.h"

#include "OfferDefinitionLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UOfferDefinitionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="OfferDefinition To JSON String")
	static FString OfferDefinitionToJsonString(const UOfferDefinition* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make OfferDefinition", meta=(DefaultToSelf="Outer", AdvancedDisplay="LootRoll, Metadata, ObtainItems, ObtainCurrency, Outer", NativeMakeFunc))
	static UOfferDefinition* Make(FString Symbol, TArray<FString> Titles, TArray<FString> Images, TArray<FString> Descriptions, TArray<FString> Obtain, FOptionalCommerceLootRoll LootRoll, FOptionalString Metadata, FOptionalArrayOfItemCreateRequestBody ObtainItems, FOptionalArrayOfCurrencyChange ObtainCurrency, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break OfferDefinition", meta=(NativeBreakFunc))
	static void Break(const UOfferDefinition* Serializable, FString& Symbol, TArray<FString>& Titles, TArray<FString>& Images, TArray<FString>& Descriptions, TArray<FString>& Obtain, FOptionalCommerceLootRoll& LootRoll, FOptionalString& Metadata, FOptionalArrayOfItemCreateRequestBody& ObtainItems, FOptionalArrayOfCurrencyChange& ObtainCurrency);
};