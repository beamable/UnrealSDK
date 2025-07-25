
#include "BeamableCore/Public/AutoGen/NewItemRewardLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UNewItemRewardLibrary::NewItemRewardToJsonString(const UNewItemReward* Serializable, const bool Pretty)
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

UNewItemReward* UNewItemRewardLibrary::Make(FString Symbol, FOptionalMapOfString Properties, UObject* Outer)
{
	auto Serializable = NewObject<UNewItemReward>(Outer);
	Serializable->Symbol = Symbol;
	Serializable->Properties = Properties;
	
	return Serializable;
}

void UNewItemRewardLibrary::Break(const UNewItemReward* Serializable, FString& Symbol, FOptionalMapOfString& Properties)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Symbol = Serializable->Symbol;
		Properties = Serializable->Properties;
	}
		
}

