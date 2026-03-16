
#include "BeamableCore/Public/AutoGen/GetBinaryDownloadUrlsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetBinaryDownloadUrlsResponseLibrary::GetBinaryDownloadUrlsResponseToJsonString(const UGetBinaryDownloadUrlsResponse* Serializable, const bool Pretty)
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

UGetBinaryDownloadUrlsResponse* UGetBinaryDownloadUrlsResponseLibrary::Make(TArray<UBinaryContentReference*> Urls, UObject* Outer)
{
	auto Serializable = NewObject<UGetBinaryDownloadUrlsResponse>(Outer);
	Serializable->Urls = Urls;
	
	return Serializable;
}

void UGetBinaryDownloadUrlsResponseLibrary::Break(const UGetBinaryDownloadUrlsResponse* Serializable, TArray<UBinaryContentReference*>& Urls)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Urls = Serializable->Urls;
	}
		
}

