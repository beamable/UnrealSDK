
#include "BeamableCore/Public/AutoGen/GetServiceURLsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetServiceURLsRequestBodyLibrary::GetServiceURLsRequestBodyToJsonString(const UGetServiceURLsRequestBody* Serializable, const bool Pretty)
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

UGetServiceURLsRequestBody* UGetServiceURLsRequestBodyLibrary::Make(TArray<UServiceImageLayers*> Requests, UObject* Outer)
{
	auto Serializable = NewObject<UGetServiceURLsRequestBody>(Outer);
	Serializable->Requests = Requests;
	
	return Serializable;
}

void UGetServiceURLsRequestBodyLibrary::Break(const UGetServiceURLsRequestBody* Serializable, TArray<UServiceImageLayers*>& Requests)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Requests = Serializable->Requests;
	}
		
}

