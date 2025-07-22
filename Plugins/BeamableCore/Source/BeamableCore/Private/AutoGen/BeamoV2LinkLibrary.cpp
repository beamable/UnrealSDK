
#include "BeamableCore/Public/AutoGen/BeamoV2LinkLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2LinkLibrary::BeamoV2LinkToJsonString(const UBeamoV2Link* Serializable, const bool Pretty)
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

UBeamoV2Link* UBeamoV2LinkLibrary::Make(FOptionalString Href, FOptionalString Rel, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2Link>(Outer);
	Serializable->Href = Href;
	Serializable->Rel = Rel;
	
	return Serializable;
}

void UBeamoV2LinkLibrary::Break(const UBeamoV2Link* Serializable, FOptionalString& Href, FOptionalString& Rel)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Href = Serializable->Href;
		Rel = Serializable->Rel;
	}
		
}

