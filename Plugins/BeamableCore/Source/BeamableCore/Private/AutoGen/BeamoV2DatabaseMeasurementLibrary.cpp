
#include "BeamableCore/Public/AutoGen/BeamoV2DatabaseMeasurementLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2DatabaseMeasurementLibrary::BeamoV2DatabaseMeasurementToJsonString(const UBeamoV2DatabaseMeasurement* Serializable, const bool Pretty)
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

UBeamoV2DatabaseMeasurement* UBeamoV2DatabaseMeasurementLibrary::Make(FString Name, FString Units, FOptionalArrayOfBeamoV2DataPoint DataPoints, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2DatabaseMeasurement>(Outer);
	Serializable->Name = Name;
	Serializable->Units = Units;
	Serializable->DataPoints = DataPoints;
	
	return Serializable;
}

void UBeamoV2DatabaseMeasurementLibrary::Break(const UBeamoV2DatabaseMeasurement* Serializable, FString& Name, FString& Units, FOptionalArrayOfBeamoV2DataPoint& DataPoints)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Units = Serializable->Units;
		DataPoints = Serializable->DataPoints;
	}
		
}

