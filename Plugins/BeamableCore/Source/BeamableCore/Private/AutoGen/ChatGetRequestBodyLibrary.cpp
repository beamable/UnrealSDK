
#include "AutoGen/ChatGetRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UChatGetRequestBodyLibrary::ChatGetRequestBodyToJsonString(const UChatGetRequestBody* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UChatGetRequestBody* UChatGetRequestBodyLibrary::Make(FOptionalString Scope, UObject* Outer)
{
	auto Serializable = NewObject<UChatGetRequestBody>(Outer);
	Serializable->Scope = Scope;
	
	return Serializable;
}

void UChatGetRequestBodyLibrary::Break(const UChatGetRequestBody* Serializable, FOptionalString& Scope)
{
	Scope = Serializable->Scope;
		
}

