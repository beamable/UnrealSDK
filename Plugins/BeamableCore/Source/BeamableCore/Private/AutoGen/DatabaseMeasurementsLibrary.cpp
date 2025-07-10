
#include "BeamableCore/Public/AutoGen/DatabaseMeasurementsLibrary.h"

#include "CoreMinimal.h"


FString UDatabaseMeasurementsLibrary::DatabaseMeasurementsToJsonString(const UDatabaseMeasurements* Serializable, const bool Pretty)
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

UDatabaseMeasurements* UDatabaseMeasurementsLibrary::Make(FString DatabaseName, FOptionalString Granularity, FOptionalString GroupId, FOptionalString HostId, FOptionalString ProcessId, FOptionalDateTime Start, FOptionalDateTime End, FOptionalArrayOfLink Links, FOptionalArrayOfDatabaseMeasurement Measurements, UObject* Outer)
{
	auto Serializable = NewObject<UDatabaseMeasurements>(Outer);
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

void UDatabaseMeasurementsLibrary::Break(const UDatabaseMeasurements* Serializable, FString& DatabaseName, FOptionalString& Granularity, FOptionalString& GroupId, FOptionalString& HostId, FOptionalString& ProcessId, FOptionalDateTime& Start, FOptionalDateTime& End, FOptionalArrayOfLink& Links, FOptionalArrayOfDatabaseMeasurement& Measurements)
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

