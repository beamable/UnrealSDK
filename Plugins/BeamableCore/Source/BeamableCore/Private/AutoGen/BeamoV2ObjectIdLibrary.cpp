
#include "BeamableCore/Public/AutoGen/BeamoV2ObjectIdLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ObjectIdLibrary::BeamoV2ObjectIdToJsonString(const UBeamoV2ObjectId* Serializable, const bool Pretty)
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

UBeamoV2ObjectId* UBeamoV2ObjectIdLibrary::Make(FOptionalInt32 Timestamp, FOptionalDateTime CreationTime, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ObjectId>(Outer);
	Serializable->Timestamp = Timestamp;
	Serializable->CreationTime = CreationTime;
	
	return Serializable;
}

void UBeamoV2ObjectIdLibrary::Break(const UBeamoV2ObjectId* Serializable, FOptionalInt32& Timestamp, FOptionalDateTime& CreationTime)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Timestamp = Serializable->Timestamp;
		CreationTime = Serializable->CreationTime;
	}
		
}

