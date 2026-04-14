
#include "BeamableCore/Public/AutoGen/GetBinaryDownloadUrlsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetBinaryDownloadUrlsRequestBodyLibrary::GetBinaryDownloadUrlsRequestBodyToJsonString(const UGetBinaryDownloadUrlsRequestBody* Serializable, const bool Pretty)
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

UGetBinaryDownloadUrlsRequestBody* UGetBinaryDownloadUrlsRequestBodyLibrary::Make(TArray<UGetContentRequestBody*> Requests, FOptionalInt64 ExpirationSeconds, UObject* Outer)
{
	auto Serializable = NewObject<UGetBinaryDownloadUrlsRequestBody>(Outer);
	Serializable->Requests = Requests;
	Serializable->ExpirationSeconds = ExpirationSeconds;
	
	return Serializable;
}

void UGetBinaryDownloadUrlsRequestBodyLibrary::Break(const UGetBinaryDownloadUrlsRequestBody* Serializable, TArray<UGetContentRequestBody*>& Requests, FOptionalInt64& ExpirationSeconds)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Requests = Serializable->Requests;
		ExpirationSeconds = Serializable->ExpirationSeconds;
	}
		
}

