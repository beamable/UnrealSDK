
#include "BeamableCore/Public/AutoGen/BeamoV2QueryResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2QueryResponseLibrary::BeamoV2QueryResponseToJsonString(const UBeamoV2QueryResponse* Serializable, const bool Pretty)
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

UBeamoV2QueryResponse* UBeamoV2QueryResponseLibrary::Make(FOptionalString QueryId, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2QueryResponse>(Outer);
	Serializable->QueryId = QueryId;
	
	return Serializable;
}

void UBeamoV2QueryResponseLibrary::Break(const UBeamoV2QueryResponse* Serializable, FOptionalString& QueryId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		QueryId = Serializable->QueryId;
	}
		
}

