
#include "BeamableCore/Public/AutoGen/ServiceTemplateViewLibrary.h"

#include "CoreMinimal.h"


FString UServiceTemplateViewLibrary::ServiceTemplateViewToJsonString(const UServiceTemplateView* Serializable, const bool Pretty)
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

UServiceTemplateView* UServiceTemplateViewLibrary::Make(FOptionalString Id, UObject* Outer)
{
	auto Serializable = NewObject<UServiceTemplateView>(Outer);
	Serializable->Id = Id;
	
	return Serializable;
}

void UServiceTemplateViewLibrary::Break(const UServiceTemplateView* Serializable, FOptionalString& Id)
{
	Id = Serializable->Id;
		
}

