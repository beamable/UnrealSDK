
#include "BeamableCore/Public/AutoGen/ClientDataEntryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UClientDataEntryLibrary::ClientDataEntryToJsonString(const UClientDataEntry* Serializable, const bool Pretty)
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

UClientDataEntry* UClientDataEntryLibrary::Make(FString Name, FString Value, UObject* Outer)
{
	auto Serializable = NewObject<UClientDataEntry>(Outer);
	Serializable->Name = Name;
	Serializable->Value = Value;
	
	return Serializable;
}

void UClientDataEntryLibrary::Break(const UClientDataEntry* Serializable, FString& Name, FString& Value)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Value = Serializable->Value;
	}
		
}

