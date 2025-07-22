
#include "BeamableCore/Public/AutoGen/BeamoV2DataPointLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2DataPointLibrary::BeamoV2DataPointToJsonString(const UBeamoV2DataPoint* Serializable, const bool Pretty)
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

UBeamoV2DataPoint* UBeamoV2DataPointLibrary::Make(double Value, FOptionalDateTime TimeStamp, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2DataPoint>(Outer);
	Serializable->Value = Value;
	Serializable->TimeStamp = TimeStamp;
	
	return Serializable;
}

void UBeamoV2DataPointLibrary::Break(const UBeamoV2DataPoint* Serializable, double& Value, FOptionalDateTime& TimeStamp)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Value = Serializable->Value;
		TimeStamp = Serializable->TimeStamp;
	}
		
}

