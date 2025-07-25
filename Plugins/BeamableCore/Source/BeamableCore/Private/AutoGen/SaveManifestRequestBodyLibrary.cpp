
#include "BeamableCore/Public/AutoGen/SaveManifestRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USaveManifestRequestBodyLibrary::SaveManifestRequestBodyToJsonString(const USaveManifestRequestBody* Serializable, const bool Pretty)
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

USaveManifestRequestBody* USaveManifestRequestBodyLibrary::Make(FBeamContentManifestId Id, TArray<UReferenceSuperset*> References, UObject* Outer)
{
	auto Serializable = NewObject<USaveManifestRequestBody>(Outer);
	Serializable->Id = Id;
	Serializable->References = References;
	
	return Serializable;
}

void USaveManifestRequestBodyLibrary::Break(const USaveManifestRequestBody* Serializable, FBeamContentManifestId& Id, TArray<UReferenceSuperset*>& References)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		References = Serializable->References;
	}
		
}

