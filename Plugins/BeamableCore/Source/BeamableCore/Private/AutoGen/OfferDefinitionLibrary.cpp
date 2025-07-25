
#include "BeamableCore/Public/AutoGen/OfferDefinitionLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UOfferDefinitionLibrary::OfferDefinitionToJsonString(const UOfferDefinition* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UOfferDefinition* UOfferDefinitionLibrary::Make(FString Symbol, TArray<FString> Titles, TArray<FString> Images, TArray<FString> Descriptions, TArray<FString> Obtain, FOptionalCommerceLootRoll LootRoll, FOptionalString Metadata, FOptionalArrayOfItemCreateRequestBody ObtainItems, FOptionalArrayOfCurrencyChange ObtainCurrency, UObject* Outer)
{
	auto Serializable = NewObject<UOfferDefinition>(Outer);
	Serializable->Symbol = Symbol;
	Serializable->Titles = Titles;
	Serializable->Images = Images;
	Serializable->Descriptions = Descriptions;
	Serializable->Obtain = Obtain;
	Serializable->LootRoll = LootRoll;
	Serializable->Metadata = Metadata;
	Serializable->ObtainItems = ObtainItems;
	Serializable->ObtainCurrency = ObtainCurrency;
	
	return Serializable;
}

void UOfferDefinitionLibrary::Break(const UOfferDefinition* Serializable, FString& Symbol, TArray<FString>& Titles, TArray<FString>& Images, TArray<FString>& Descriptions, TArray<FString>& Obtain, FOptionalCommerceLootRoll& LootRoll, FOptionalString& Metadata, FOptionalArrayOfItemCreateRequestBody& ObtainItems, FOptionalArrayOfCurrencyChange& ObtainCurrency)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Symbol = Serializable->Symbol;
		Titles = Serializable->Titles;
		Images = Serializable->Images;
		Descriptions = Serializable->Descriptions;
		Obtain = Serializable->Obtain;
		LootRoll = Serializable->LootRoll;
		Metadata = Serializable->Metadata;
		ObtainItems = Serializable->ObtainItems;
		ObtainCurrency = Serializable->ObtainCurrency;
	}
		
}

