
#include "BeamableCore/Public/AutoGen/PreSignedUrlsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPreSignedUrlsResponseLibrary::PreSignedUrlsResponseToJsonString(const UPreSignedUrlsResponse* Serializable, const bool Pretty)
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

UPreSignedUrlsResponse* UPreSignedUrlsResponseLibrary::Make(TArray<UBeamoBasicURLResponse*> Response, UObject* Outer)
{
	auto Serializable = NewObject<UPreSignedUrlsResponse>(Outer);
	Serializable->Response = Response;
	
	return Serializable;
}

void UPreSignedUrlsResponseLibrary::Break(const UPreSignedUrlsResponse* Serializable, TArray<UBeamoBasicURLResponse*>& Response)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Response = Serializable->Response;
	}
		
}

