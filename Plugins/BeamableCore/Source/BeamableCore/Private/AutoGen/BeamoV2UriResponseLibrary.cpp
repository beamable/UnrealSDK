
#include "BeamableCore/Public/AutoGen/BeamoV2UriResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2UriResponseLibrary::BeamoV2UriResponseToJsonString(const UBeamoV2UriResponse* Serializable, const bool Pretty)
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

UBeamoV2UriResponse* UBeamoV2UriResponseLibrary::Make(FOptionalString Uri, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2UriResponse>(Outer);
	Serializable->Uri = Uri;
	
	return Serializable;
}

void UBeamoV2UriResponseLibrary::Break(const UBeamoV2UriResponse* Serializable, FOptionalString& Uri)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Uri = Serializable->Uri;
	}
		
}

