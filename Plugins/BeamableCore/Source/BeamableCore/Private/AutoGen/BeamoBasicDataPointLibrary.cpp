
#include "BeamableCore/Public/AutoGen/BeamoBasicDataPointLibrary.h"

#include "CoreMinimal.h"


FString UBeamoBasicDataPointLibrary::BeamoBasicDataPointToJsonString(const UBeamoBasicDataPoint* Serializable, const bool Pretty)
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

UBeamoBasicDataPoint* UBeamoBasicDataPointLibrary::Make(FString Timestamp, FString Value, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoBasicDataPoint>(Outer);
	Serializable->Timestamp = Timestamp;
	Serializable->Value = Value;
	
	return Serializable;
}

void UBeamoBasicDataPointLibrary::Break(const UBeamoBasicDataPoint* Serializable, FString& Timestamp, FString& Value)
{
	Timestamp = Serializable->Timestamp;
	Value = Serializable->Value;
		
}

