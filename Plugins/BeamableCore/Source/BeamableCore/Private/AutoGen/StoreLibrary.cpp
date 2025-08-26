
#include "BeamableCore/Public/AutoGen/StoreLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UStoreLibrary::StoreToJsonString(const UStore* Serializable, const bool Pretty)
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

UStore* UStoreLibrary::Make(FString Symbol, TArray<UListing*> Listings, FOptionalBool bShowInactiveListings, FOptionalInt32 ActiveListingLimit, FOptionalInt32 Choose, FOptionalInt32 RefreshTime, FOptionalString Title, UObject* Outer)
{
	auto Serializable = NewObject<UStore>(Outer);
	Serializable->Symbol = Symbol;
	Serializable->Listings = Listings;
	Serializable->bShowInactiveListings = bShowInactiveListings;
	Serializable->ActiveListingLimit = ActiveListingLimit;
	Serializable->Choose = Choose;
	Serializable->RefreshTime = RefreshTime;
	Serializable->Title = Title;
	
	return Serializable;
}

void UStoreLibrary::Break(const UStore* Serializable, FString& Symbol, TArray<UListing*>& Listings, FOptionalBool& bShowInactiveListings, FOptionalInt32& ActiveListingLimit, FOptionalInt32& Choose, FOptionalInt32& RefreshTime, FOptionalString& Title)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Symbol = Serializable->Symbol;
		Listings = Serializable->Listings;
		bShowInactiveListings = Serializable->bShowInactiveListings;
		ActiveListingLimit = Serializable->ActiveListingLimit;
		Choose = Serializable->Choose;
		RefreshTime = Serializable->RefreshTime;
		Title = Serializable->Title;
	}
		
}

