
#include "BeamableCore/Public/AutoGen/UploadURLLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUploadURLLibrary::UploadURLToJsonString(const UUploadURL* Serializable, const bool Pretty)
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

UUploadURL* UUploadURLLibrary::Make(FString Key, FString Url, UObject* Outer)
{
	auto Serializable = NewObject<UUploadURL>(Outer);
	Serializable->Key = Key;
	Serializable->Url = Url;
	
	return Serializable;
}

void UUploadURLLibrary::Break(const UUploadURL* Serializable, FString& Key, FString& Url)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Key = Serializable->Key;
		Url = Serializable->Url;
	}
		
}

