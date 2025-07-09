
#include "BeamableCore/Public/AutoGen/SignedRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString USignedRequestBodyLibrary::SignedRequestBodyToJsonString(const USignedRequestBody* Serializable, const bool Pretty)
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

USignedRequestBody* USignedRequestBodyLibrary::Make(FOptionalString Url, FOptionalString Body, FOptionalString Method, FOptionalArrayOfStringStringKeyValuePair Headers, UObject* Outer)
{
	auto Serializable = NewObject<USignedRequestBody>(Outer);
	Serializable->Url = Url;
	Serializable->Body = Body;
	Serializable->Method = Method;
	Serializable->Headers = Headers;
	
	return Serializable;
}

void USignedRequestBodyLibrary::Break(const USignedRequestBody* Serializable, FOptionalString& Url, FOptionalString& Body, FOptionalString& Method, FOptionalArrayOfStringStringKeyValuePair& Headers)
{
	Url = Serializable->Url;
	Body = Serializable->Body;
	Method = Serializable->Method;
	Headers = Serializable->Headers;
		
}

