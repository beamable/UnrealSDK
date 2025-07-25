
#include "BeamableCore/Public/AutoGen/AttachmentPropertyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAttachmentPropertyLibrary::AttachmentPropertyToJsonString(const UAttachmentProperty* Serializable, const bool Pretty)
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

UAttachmentProperty* UAttachmentPropertyLibrary::Make(FString Name, FString Value, UObject* Outer)
{
	auto Serializable = NewObject<UAttachmentProperty>(Outer);
	Serializable->Name = Name;
	Serializable->Value = Value;
	
	return Serializable;
}

void UAttachmentPropertyLibrary::Break(const UAttachmentProperty* Serializable, FString& Name, FString& Value)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Value = Serializable->Value;
	}
		
}

