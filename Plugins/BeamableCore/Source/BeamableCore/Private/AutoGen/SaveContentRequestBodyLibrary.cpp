
#include "BeamableCore/Public/AutoGen/SaveContentRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString USaveContentRequestBodyLibrary::SaveContentRequestBodyToJsonString(const USaveContentRequestBody* Serializable, const bool Pretty)
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

USaveContentRequestBody* USaveContentRequestBodyLibrary::Make(TArray<UContentDefinition*> Content, UObject* Outer)
{
	auto Serializable = NewObject<USaveContentRequestBody>(Outer);
	Serializable->Content = Content;
	
	return Serializable;
}

void USaveContentRequestBodyLibrary::Break(const USaveContentRequestBody* Serializable, TArray<UContentDefinition*>& Content)
{
	Content = Serializable->Content;
		
}

