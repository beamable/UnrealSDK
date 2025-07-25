
#include "BeamableCore/Public/AutoGen/GetActiveOffersResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetActiveOffersResponseLibrary::GetActiveOffersResponseToJsonString(const UGetActiveOffersResponse* Serializable, const bool Pretty)
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

UGetActiveOffersResponse* UGetActiveOffersResponseLibrary::Make(TArray<UPlayerStoreView*> Stores, UObject* Outer)
{
	auto Serializable = NewObject<UGetActiveOffersResponse>(Outer);
	Serializable->Stores = Stores;
	
	return Serializable;
}

void UGetActiveOffersResponseLibrary::Break(const UGetActiveOffersResponse* Serializable, TArray<UPlayerStoreView*>& Stores)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Stores = Serializable->Stores;
	}
		
}

