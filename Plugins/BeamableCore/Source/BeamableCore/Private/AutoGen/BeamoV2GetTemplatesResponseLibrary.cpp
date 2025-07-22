
#include "BeamableCore/Public/AutoGen/BeamoV2GetTemplatesResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2GetTemplatesResponseLibrary::BeamoV2GetTemplatesResponseToJsonString(const UBeamoV2GetTemplatesResponse* Serializable, const bool Pretty)
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

UBeamoV2GetTemplatesResponse* UBeamoV2GetTemplatesResponseLibrary::Make(FOptionalArrayOfBeamoV2ServiceTemplateView Templates, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2GetTemplatesResponse>(Outer);
	Serializable->Templates = Templates;
	
	return Serializable;
}

void UBeamoV2GetTemplatesResponseLibrary::Break(const UBeamoV2GetTemplatesResponse* Serializable, FOptionalArrayOfBeamoV2ServiceTemplateView& Templates)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Templates = Serializable->Templates;
	}
		
}

