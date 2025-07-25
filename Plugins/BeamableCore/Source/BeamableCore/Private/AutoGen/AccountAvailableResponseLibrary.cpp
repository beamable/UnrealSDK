
#include "BeamableCore/Public/AutoGen/AccountAvailableResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAccountAvailableResponseLibrary::AccountAvailableResponseToJsonString(const UAccountAvailableResponse* Serializable, const bool Pretty)
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

UAccountAvailableResponse* UAccountAvailableResponseLibrary::Make(bool bAvailable, UObject* Outer)
{
	auto Serializable = NewObject<UAccountAvailableResponse>(Outer);
	Serializable->bAvailable = bAvailable;
	
	return Serializable;
}

void UAccountAvailableResponseLibrary::Break(const UAccountAvailableResponse* Serializable, bool& bAvailable)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bAvailable = Serializable->bAvailable;
	}
		
}

