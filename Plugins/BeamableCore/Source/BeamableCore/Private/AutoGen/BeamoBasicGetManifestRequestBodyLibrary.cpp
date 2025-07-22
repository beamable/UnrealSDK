
#include "BeamableCore/Public/AutoGen/BeamoBasicGetManifestRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoBasicGetManifestRequestBodyLibrary::BeamoBasicGetManifestRequestBodyToJsonString(const UBeamoBasicGetManifestRequestBody* Serializable, const bool Pretty)
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

UBeamoBasicGetManifestRequestBody* UBeamoBasicGetManifestRequestBodyLibrary::Make(FString Id, FOptionalBool bArchived, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoBasicGetManifestRequestBody>(Outer);
	Serializable->Id = Id;
	Serializable->bArchived = bArchived;
	
	return Serializable;
}

void UBeamoBasicGetManifestRequestBodyLibrary::Break(const UBeamoBasicGetManifestRequestBody* Serializable, FString& Id, FOptionalBool& bArchived)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		bArchived = Serializable->bArchived;
	}
		
}

