
#include "BeamableCore/Public/AutoGen/LinkLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


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

ULink* ULinkLibrary::Make(FString Href, FString Rel, UObject* Outer)
{
	auto Serializable = NewObject<ULink>(Outer);
	Serializable->Href = Href;
	Serializable->Rel = Rel;
	
	return Serializable;
}

void ULinkLibrary::Break(const ULink* Serializable, FString& Href, FString& Rel)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Href = Serializable->Href;
		Rel = Serializable->Rel;
	}
		
}

