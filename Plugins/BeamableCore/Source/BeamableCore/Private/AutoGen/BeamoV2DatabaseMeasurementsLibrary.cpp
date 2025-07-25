
#include "BeamableCore/Public/AutoGen/BeamoV2DatabaseMeasurementsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2DatabaseMeasurementsLibrary::BeamoV2DatabaseMeasurementsToJsonString(const UBeamoV2DatabaseMeasurements* Serializable, const bool Pretty)
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

UBeamoV2DatabaseMeasurements* UBeamoV2DatabaseMeasurementsLibrary::Make(FString DatabaseName, FOptionalString Granularity, FOptionalString GroupId, FOptionalString HostId, FOptionalString ProcessId, FOptionalDateTime Start, FOptionalDateTime End, FOptionalArrayOfBeamoV2Link Links, FOptionalArrayOfBeamoV2DatabaseMeasurement Measurements, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2DatabaseMeasurements>(Outer);
	Serializable->DatabaseName = DatabaseName;
	Serializable->Granularity = Granularity;
	Serializable->GroupId = GroupId;
	Serializable->HostId = HostId;
	Serializable->ProcessId = ProcessId;
	Serializable->Start = Start;
	Serializable->End = End;
	Serializable->Links = Links;
	Serializable->Measurements = Measurements;
	
	return Serializable;
}

void UBeamoV2DatabaseMeasurementsLibrary::Break(const UBeamoV2DatabaseMeasurements* Serializable, FString& DatabaseName, FOptionalString& Granularity, FOptionalString& GroupId, FOptionalString& HostId, FOptionalString& ProcessId, FOptionalDateTime& Start, FOptionalDateTime& End, FOptionalArrayOfBeamoV2Link& Links, FOptionalArrayOfBeamoV2DatabaseMeasurement& Measurements)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		DatabaseName = Serializable->DatabaseName;
		Granularity = Serializable->Granularity;
		GroupId = Serializable->GroupId;
		HostId = Serializable->HostId;
		ProcessId = Serializable->ProcessId;
		Start = Serializable->Start;
		End = Serializable->End;
		Links = Serializable->Links;
		Measurements = Serializable->Measurements;
	}
		
}

