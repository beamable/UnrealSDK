
#include "BeamableCore/Public/AutoGen/ItemPropertyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UItemPropertyLibrary::ItemPropertyToJsonString(const UItemProperty* Serializable, const bool Pretty)
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

UItemProperty* UItemPropertyLibrary::Make(FString Name, FString Value, UObject* Outer)
{
	auto Serializable = NewObject<UItemProperty>(Outer);
	Serializable->Name = Name;
	Serializable->Value = Value;
	
	return Serializable;
}

void UItemPropertyLibrary::Break(const UItemProperty* Serializable, FString& Name, FString& Value)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Value = Serializable->Value;
	}
		
}

