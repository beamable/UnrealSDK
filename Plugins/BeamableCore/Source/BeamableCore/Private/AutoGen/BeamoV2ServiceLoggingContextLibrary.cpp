
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceLoggingContextLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ServiceLoggingContextLibrary::BeamoV2ServiceLoggingContextToJsonString(const UBeamoV2ServiceLoggingContext* Serializable, const bool Pretty)
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

UBeamoV2ServiceLoggingContext* UBeamoV2ServiceLoggingContextLibrary::Make(FString ServiceName, FString RoutingKey, EBeamBeamoV2LogLevel DefaultLogLevel, FOptionalString Id, FOptionalArrayOfBeamoV2LogContextRule Rules, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ServiceLoggingContext>(Outer);
	Serializable->ServiceName = ServiceName;
	Serializable->RoutingKey = RoutingKey;
	Serializable->DefaultLogLevel = DefaultLogLevel;
	Serializable->Id = Id;
	Serializable->Rules = Rules;
	
	return Serializable;
}

void UBeamoV2ServiceLoggingContextLibrary::Break(const UBeamoV2ServiceLoggingContext* Serializable, FString& ServiceName, FString& RoutingKey, EBeamBeamoV2LogLevel& DefaultLogLevel, FOptionalString& Id, FOptionalArrayOfBeamoV2LogContextRule& Rules)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ServiceName = Serializable->ServiceName;
		RoutingKey = Serializable->RoutingKey;
		DefaultLogLevel = Serializable->DefaultLogLevel;
		Id = Serializable->Id;
		Rules = Serializable->Rules;
	}
		
}

