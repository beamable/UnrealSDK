
#include "BeamableCore/Public/AutoGen/SKULibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USKULibrary::SKUToJsonString(const USKU* Serializable, const bool Pretty)
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

USKU* USKULibrary::Make(FString Name, FString Description, int32 RealPrice, TMap<FString, FString> ProductIds, UObject* Outer)
{
	auto Serializable = NewObject<USKU>(Outer);
	Serializable->Name = Name;
	Serializable->Description = Description;
	Serializable->RealPrice = RealPrice;
	Serializable->ProductIds = ProductIds;
	
	return Serializable;
}

void USKULibrary::Break(const USKU* Serializable, FString& Name, FString& Description, int32& RealPrice, TMap<FString, FString>& ProductIds)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Description = Serializable->Description;
		RealPrice = Serializable->RealPrice;
		ProductIds = Serializable->ProductIds;
	}
		
}

