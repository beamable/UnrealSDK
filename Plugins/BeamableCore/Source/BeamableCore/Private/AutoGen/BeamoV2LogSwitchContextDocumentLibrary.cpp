
#include "BeamableCore/Public/AutoGen/BeamoV2LogSwitchContextDocumentLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2LogSwitchContextDocumentLibrary::BeamoV2LogSwitchContextDocumentToJsonString(const UBeamoV2LogSwitchContextDocument* Serializable, const bool Pretty)
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

UBeamoV2LogSwitchContextDocument* UBeamoV2LogSwitchContextDocumentLibrary::Make(FString ServiceName, FString RoutingKey, EBeamBeamoV2LogLevel DefaultLogLevel, FOptionalBeamoV2ObjectId Id, FOptionalArrayOfBeamoV2LogContextRule Rules, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2LogSwitchContextDocument>(Outer);
	Serializable->ServiceName = ServiceName;
	Serializable->RoutingKey = RoutingKey;
	Serializable->DefaultLogLevel = DefaultLogLevel;
	Serializable->Id = Id;
	Serializable->Rules = Rules;
	
	return Serializable;
}

void UBeamoV2LogSwitchContextDocumentLibrary::Break(const UBeamoV2LogSwitchContextDocument* Serializable, FString& ServiceName, FString& RoutingKey, EBeamBeamoV2LogLevel& DefaultLogLevel, FOptionalBeamoV2ObjectId& Id, FOptionalArrayOfBeamoV2LogContextRule& Rules)
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

