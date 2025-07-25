
#include "BeamableCore/Public/AutoGen/DatabaseMeasurementsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


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

UDatabaseMeasurements* UDatabaseMeasurementsLibrary::Make(FString DatabaseName, TArray<ULink*> Links, FOptionalString GroupId, FOptionalString HostId, FOptionalString Granularity, FOptionalString End, FOptionalString Start, FOptionalString ProcessId, FOptionalArrayOfDatabaseMeasurement Measurements, UObject* Outer)
{
	auto Serializable = NewObject<UDatabaseMeasurements>(Outer);
	Serializable->DatabaseName = DatabaseName;
	Serializable->Links = Links;
	Serializable->GroupId = GroupId;
	Serializable->HostId = HostId;
	Serializable->Granularity = Granularity;
	Serializable->End = End;
	Serializable->Start = Start;
	Serializable->ProcessId = ProcessId;
	Serializable->Measurements = Measurements;
	
	return Serializable;
}

void UDatabaseMeasurementsLibrary::Break(const UDatabaseMeasurements* Serializable, FString& DatabaseName, TArray<ULink*>& Links, FOptionalString& GroupId, FOptionalString& HostId, FOptionalString& Granularity, FOptionalString& End, FOptionalString& Start, FOptionalString& ProcessId, FOptionalArrayOfDatabaseMeasurement& Measurements)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		DatabaseName = Serializable->DatabaseName;
		Links = Serializable->Links;
		GroupId = Serializable->GroupId;
		HostId = Serializable->HostId;
		Granularity = Serializable->Granularity;
		End = Serializable->End;
		Start = Serializable->Start;
		ProcessId = Serializable->ProcessId;
		Measurements = Serializable->Measurements;
	}
		
}

