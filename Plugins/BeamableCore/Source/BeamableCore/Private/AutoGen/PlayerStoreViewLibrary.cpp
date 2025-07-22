
#include "BeamableCore/Public/AutoGen/PlayerStoreViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPlayerStoreViewLibrary::PlayerStoreViewToJsonString(const UPlayerStoreView* Serializable, const bool Pretty)
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

UPlayerStoreView* UPlayerStoreViewLibrary::Make(FString Symbol, TArray<UPlayerListingView*> Listings, FOptionalInt64 NextDeltaSeconds, FOptionalString Title, FOptionalInt64 SecondsRemain, UObject* Outer)
{
	auto Serializable = NewObject<UPlayerStoreView>(Outer);
	Serializable->Symbol = Symbol;
	Serializable->Listings = Listings;
	Serializable->NextDeltaSeconds = NextDeltaSeconds;
	Serializable->Title = Title;
	Serializable->SecondsRemain = SecondsRemain;
	
	return Serializable;
}

void UPlayerStoreViewLibrary::Break(const UPlayerStoreView* Serializable, FString& Symbol, TArray<UPlayerListingView*>& Listings, FOptionalInt64& NextDeltaSeconds, FOptionalString& Title, FOptionalInt64& SecondsRemain)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Symbol = Serializable->Symbol;
		Listings = Serializable->Listings;
		NextDeltaSeconds = Serializable->NextDeltaSeconds;
		Title = Serializable->Title;
		SecondsRemain = Serializable->SecondsRemain;
	}
		
}

