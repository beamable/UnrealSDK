
#include "BeamableCore/Public/AutoGen/SaveManifestResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USaveManifestResponseLibrary::SaveManifestResponseToJsonString(const USaveManifestResponse* Serializable, const bool Pretty)
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

USaveManifestResponse* USaveManifestResponseLibrary::Make(FString Id, FString Checksum, FString Uid, int64 Created, FOptionalString DiffUrl, UObject* Outer)
{
	auto Serializable = NewObject<USaveManifestResponse>(Outer);
	Serializable->Id = Id;
	Serializable->Checksum = Checksum;
	Serializable->Uid = Uid;
	Serializable->Created = Created;
	Serializable->DiffUrl = DiffUrl;
	
	return Serializable;
}

void USaveManifestResponseLibrary::Break(const USaveManifestResponse* Serializable, FString& Id, FString& Checksum, FString& Uid, int64& Created, FOptionalString& DiffUrl)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Checksum = Serializable->Checksum;
		Uid = Serializable->Uid;
		Created = Serializable->Created;
		DiffUrl = Serializable->DiffUrl;
	}
		
}

