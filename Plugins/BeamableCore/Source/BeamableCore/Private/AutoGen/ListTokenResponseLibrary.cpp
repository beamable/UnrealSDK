
#include "BeamableCore/Public/AutoGen/ListTokenResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UListTokenResponseLibrary::ListTokenResponseToJsonString(const UListTokenResponse* Serializable, const bool Pretty)
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

UListTokenResponse* UListTokenResponseLibrary::Make(TArray<UListTokenResponseItem*> Items, UObject* Outer)
{
	auto Serializable = NewObject<UListTokenResponse>(Outer);
	Serializable->Items = Items;
	
	return Serializable;
}

void UListTokenResponseLibrary::Break(const UListTokenResponse* Serializable, TArray<UListTokenResponseItem*>& Items)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Items = Serializable->Items;
	}
		
}

