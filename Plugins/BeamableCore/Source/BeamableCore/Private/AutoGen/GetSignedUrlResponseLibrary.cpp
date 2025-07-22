
#include "BeamableCore/Public/AutoGen/GetSignedUrlResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetSignedUrlResponseLibrary::GetSignedUrlResponseToJsonString(const UGetSignedUrlResponse* Serializable, const bool Pretty)
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

UGetSignedUrlResponse* UGetSignedUrlResponseLibrary::Make(FString Url, FString Body, FString Method, TArray<UGetLogsUrlHeader*> Headers, UObject* Outer)
{
	auto Serializable = NewObject<UGetSignedUrlResponse>(Outer);
	Serializable->Url = Url;
	Serializable->Body = Body;
	Serializable->Method = Method;
	Serializable->Headers = Headers;
	
	return Serializable;
}

void UGetSignedUrlResponseLibrary::Break(const UGetSignedUrlResponse* Serializable, FString& Url, FString& Body, FString& Method, TArray<UGetLogsUrlHeader*>& Headers)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Url = Serializable->Url;
		Body = Serializable->Body;
		Method = Serializable->Method;
		Headers = Serializable->Headers;
	}
		
}

