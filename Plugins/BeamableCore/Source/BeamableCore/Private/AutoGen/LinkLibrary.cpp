
#include "BeamableCore/Public/AutoGen/LinkLibrary.h"

#include "CoreMinimal.h"


FString ULinkLibrary::LinkToJsonString(const ULink* Serializable, const bool Pretty)
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

ULink* ULinkLibrary::Make(FOptionalString Href, FOptionalString Rel, UObject* Outer)
{
	auto Serializable = NewObject<ULink>(Outer);
	Serializable->Href = Href;
	Serializable->Rel = Rel;
	
	return Serializable;
}

void ULinkLibrary::Break(const ULink* Serializable, FOptionalString& Href, FOptionalString& Rel)
{
	Href = Serializable->Href;
	Rel = Serializable->Rel;
		
}

