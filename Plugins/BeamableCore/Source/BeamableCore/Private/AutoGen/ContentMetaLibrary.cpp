
#include "BeamableCore/Public/AutoGen/ContentMetaLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UContentMetaLibrary::ContentMetaToJsonString(const UContentMeta* Serializable, const bool Pretty)
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

UContentMeta* UContentMetaLibrary::Make(EBeamContentVisibility Visibility, FOptionalString Text, FOptionalBeamContentId link, FOptionalArrayOfBeamContentId links, UObject* Outer)
{
	auto Serializable = NewObject<UContentMeta>(Outer);
	Serializable->Visibility = Visibility;
	Serializable->Text = Text;
	Serializable->link = link;
	Serializable->links = links;
	
	return Serializable;
}

void UContentMetaLibrary::Break(const UContentMeta* Serializable, EBeamContentVisibility& Visibility, FOptionalString& Text, FOptionalBeamContentId& link, FOptionalArrayOfBeamContentId& links)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Visibility = Serializable->Visibility;
		Text = Serializable->Text;
		link = Serializable->link;
		links = Serializable->links;
	}
		
}

