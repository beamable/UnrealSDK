
#include "BeamableCore/Public/AutoGen/ActiveListingResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UActiveListingResponseLibrary::ActiveListingResponseToJsonString(const UActiveListingResponse* Serializable, const bool Pretty)
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

UActiveListingResponse* UActiveListingResponseLibrary::Make(FString StoreSymbol, UPlayerListingView* Listing, UObject* Outer)
{
	auto Serializable = NewObject<UActiveListingResponse>(Outer);
	Serializable->StoreSymbol = StoreSymbol;
	Serializable->Listing = Listing;
	
	return Serializable;
}

void UActiveListingResponseLibrary::Break(const UActiveListingResponse* Serializable, FString& StoreSymbol, UPlayerListingView*& Listing)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		StoreSymbol = Serializable->StoreSymbol;
		Listing = Serializable->Listing;
	}
		
}

