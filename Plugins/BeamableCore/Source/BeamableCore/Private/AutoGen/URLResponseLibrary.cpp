
#include "AutoGen/URLResponseLibrary.h"

#include "CoreMinimal.h"


FString UURLResponseLibrary::URLResponseToJsonString(const UURLResponse* Serializable, const bool Pretty)
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

UURLResponse* UURLResponseLibrary::Make(FString Url, FString ObjectKey, UObject* Outer)
{
	auto Serializable = NewObject<UURLResponse>(Outer);
	Serializable->Url = Url;
	Serializable->ObjectKey = ObjectKey;
	
	return Serializable;
}

void UURLResponseLibrary::Break(const UURLResponse* Serializable, FString& Url, FString& ObjectKey)
{
	Url = Serializable->Url;
	ObjectKey = Serializable->ObjectKey;
		
}

