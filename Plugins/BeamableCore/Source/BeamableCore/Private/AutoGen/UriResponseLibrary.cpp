
#include "BeamableCore/Public/AutoGen/UriResponseLibrary.h"

#include "CoreMinimal.h"


FString UUriResponseLibrary::UriResponseToJsonString(const UUriResponse* Serializable, const bool Pretty)
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

UUriResponse* UUriResponseLibrary::Make(FOptionalString Uri, UObject* Outer)
{
	auto Serializable = NewObject<UUriResponse>(Outer);
	Serializable->Uri = Uri;
	
	return Serializable;
}

void UUriResponseLibrary::Break(const UUriResponse* Serializable, FOptionalString& Uri)
{
	Uri = Serializable->Uri;
		
}

