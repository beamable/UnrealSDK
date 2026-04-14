
#include "BeamableCore/Public/AutoGen/BinaryContentReferenceLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBinaryContentReferenceLibrary::BinaryContentReferenceToJsonString(const UBinaryContentReference* Serializable, const bool Pretty)
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

UBinaryContentReference* UBinaryContentReferenceLibrary::Make(FString ContentId, FString Version, FString Url, UObject* Outer)
{
	auto Serializable = NewObject<UBinaryContentReference>(Outer);
	Serializable->ContentId = ContentId;
	Serializable->Version = Version;
	Serializable->Url = Url;
	
	return Serializable;
}

void UBinaryContentReferenceLibrary::Break(const UBinaryContentReference* Serializable, FString& ContentId, FString& Version, FString& Url)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ContentId = Serializable->ContentId;
		Version = Serializable->Version;
		Url = Serializable->Url;
	}
		
}

