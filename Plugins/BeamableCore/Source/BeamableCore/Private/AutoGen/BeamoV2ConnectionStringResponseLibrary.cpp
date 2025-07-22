
#include "BeamableCore/Public/AutoGen/BeamoV2ConnectionStringResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ConnectionStringResponseLibrary::BeamoV2ConnectionStringResponseToJsonString(const UBeamoV2ConnectionStringResponse* Serializable, const bool Pretty)
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

UBeamoV2ConnectionStringResponse* UBeamoV2ConnectionStringResponseLibrary::Make(FOptionalString ConnectionString, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ConnectionStringResponse>(Outer);
	Serializable->ConnectionString = ConnectionString;
	
	return Serializable;
}

void UBeamoV2ConnectionStringResponseLibrary::Break(const UBeamoV2ConnectionStringResponse* Serializable, FOptionalString& ConnectionString)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ConnectionString = Serializable->ConnectionString;
	}
		
}

