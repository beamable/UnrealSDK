
#include "BeamableCore/Public/AutoGen/GetTemplatesResponseLibrary.h"

#include "CoreMinimal.h"


FString UGetTemplatesResponseLibrary::GetTemplatesResponseToJsonString(const UGetTemplatesResponse* Serializable, const bool Pretty)
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

UGetTemplatesResponse* UGetTemplatesResponseLibrary::Make(FOptionalArrayOfServiceTemplateView Templates, UObject* Outer)
{
	auto Serializable = NewObject<UGetTemplatesResponse>(Outer);
	Serializable->Templates = Templates;
	
	return Serializable;
}

void UGetTemplatesResponseLibrary::Break(const UGetTemplatesResponse* Serializable, FOptionalArrayOfServiceTemplateView& Templates)
{
	Templates = Serializable->Templates;
		
}

