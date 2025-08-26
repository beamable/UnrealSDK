
#include "BeamableCore/Public/AutoGen/DatabaseMeasurementLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDatabaseMeasurementLibrary::DatabaseMeasurementToJsonString(const UDatabaseMeasurement* Serializable, const bool Pretty)
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

UDatabaseMeasurement* UDatabaseMeasurementLibrary::Make(FString Name, FString Units, TArray<UDataPoint*> DataPoints, UObject* Outer)
{
	auto Serializable = NewObject<UDatabaseMeasurement>(Outer);
	Serializable->Name = Name;
	Serializable->Units = Units;
	Serializable->DataPoints = DataPoints;
	
	return Serializable;
}

void UDatabaseMeasurementLibrary::Break(const UDatabaseMeasurement* Serializable, FString& Name, FString& Units, TArray<UDataPoint*>& DataPoints)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Units = Serializable->Units;
		DataPoints = Serializable->DataPoints;
	}
		
}

