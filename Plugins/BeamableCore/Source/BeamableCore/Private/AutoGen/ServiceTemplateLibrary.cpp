
#include "BeamableCore/Public/AutoGen/ServiceTemplateLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UServiceTemplateLibrary::ServiceTemplateToJsonString(const UServiceTemplate* Serializable, const bool Pretty)
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

UServiceTemplate* UServiceTemplateLibrary::Make(FString Id, UObject* Outer)
{
	auto Serializable = NewObject<UServiceTemplate>(Outer);
	Serializable->Id = Id;
	
	return Serializable;
}

void UServiceTemplateLibrary::Break(const UServiceTemplate* Serializable, FString& Id)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
	}
		
}

