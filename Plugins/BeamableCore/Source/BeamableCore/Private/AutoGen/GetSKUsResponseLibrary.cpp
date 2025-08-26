
#include "BeamableCore/Public/AutoGen/GetSKUsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetSKUsResponseLibrary::GetSKUsResponseToJsonString(const UGetSKUsResponse* Serializable, const bool Pretty)
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

UGetSKUsResponse* UGetSKUsResponseLibrary::Make(USKUDefinitions* Skus, UObject* Outer)
{
	auto Serializable = NewObject<UGetSKUsResponse>(Outer);
	Serializable->Skus = Skus;
	
	return Serializable;
}

void UGetSKUsResponseLibrary::Break(const UGetSKUsResponse* Serializable, USKUDefinitions*& Skus)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Skus = Serializable->Skus;
	}
		
}

