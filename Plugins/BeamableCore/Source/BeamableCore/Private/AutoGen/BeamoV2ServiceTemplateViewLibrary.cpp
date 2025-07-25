
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceTemplateViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ServiceTemplateViewLibrary::BeamoV2ServiceTemplateViewToJsonString(const UBeamoV2ServiceTemplateView* Serializable, const bool Pretty)
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

UBeamoV2ServiceTemplateView* UBeamoV2ServiceTemplateViewLibrary::Make(FOptionalString Id, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ServiceTemplateView>(Outer);
	Serializable->Id = Id;
	
	return Serializable;
}

void UBeamoV2ServiceTemplateViewLibrary::Break(const UBeamoV2ServiceTemplateView* Serializable, FOptionalString& Id)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
	}
		
}

