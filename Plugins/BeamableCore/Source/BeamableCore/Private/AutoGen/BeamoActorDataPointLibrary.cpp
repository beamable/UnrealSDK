
#include "BeamableCore/Public/AutoGen/BeamoActorDataPointLibrary.h"

#include "CoreMinimal.h"


FString UBeamoActorDataPointLibrary::BeamoActorDataPointToJsonString(const UBeamoActorDataPoint* Serializable, const bool Pretty)
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

UBeamoActorDataPoint* UBeamoActorDataPointLibrary::Make(double Value, FOptionalDateTime TimeStamp, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoActorDataPoint>(Outer);
	Serializable->Value = Value;
	Serializable->TimeStamp = TimeStamp;
	
	return Serializable;
}

void UBeamoActorDataPointLibrary::Break(const UBeamoActorDataPoint* Serializable, double& Value, FOptionalDateTime& TimeStamp)
{
	Value = Serializable->Value;
	TimeStamp = Serializable->TimeStamp;
		
}

