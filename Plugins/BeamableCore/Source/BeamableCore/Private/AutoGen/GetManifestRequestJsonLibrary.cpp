
#include "BeamableCore/Public/AutoGen/GetManifestRequestJsonLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetManifestRequestJsonLibrary::GetManifestRequestJsonToJsonString(const UGetManifestRequestJson* Serializable, const bool Pretty)
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

UGetManifestRequestJson* UGetManifestRequestJsonLibrary::Make(FOptionalBeamContentManifestId Id, FOptionalString Uid, UObject* Outer)
{
	auto Serializable = NewObject<UGetManifestRequestJson>(Outer);
	Serializable->Id = Id;
	Serializable->Uid = Uid;
	
	return Serializable;
}

void UGetManifestRequestJsonLibrary::Break(const UGetManifestRequestJson* Serializable, FOptionalBeamContentManifestId& Id, FOptionalString& Uid)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Uid = Serializable->Uid;
	}
		
}

