
#include "BeamableCore/Public/AutoGen/CloudsavingBasicReferenceLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCloudsavingBasicReferenceLibrary::CloudsavingBasicReferenceToJsonString(const UCloudsavingBasicReference* Serializable, const bool Pretty)
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

UCloudsavingBasicReference* UCloudsavingBasicReferenceLibrary::Make(int64 Size, int64 LastModified, FString Key, FString BucketName, FOptionalString ETag, UObject* Outer)
{
	auto Serializable = NewObject<UCloudsavingBasicReference>(Outer);
	Serializable->Size = Size;
	Serializable->LastModified = LastModified;
	Serializable->Key = Key;
	Serializable->BucketName = BucketName;
	Serializable->ETag = ETag;
	
	return Serializable;
}

void UCloudsavingBasicReferenceLibrary::Break(const UCloudsavingBasicReference* Serializable, int64& Size, int64& LastModified, FString& Key, FString& BucketName, FOptionalString& ETag)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Size = Serializable->Size;
		LastModified = Serializable->LastModified;
		Key = Serializable->Key;
		BucketName = Serializable->BucketName;
		ETag = Serializable->ETag;
	}
		
}

