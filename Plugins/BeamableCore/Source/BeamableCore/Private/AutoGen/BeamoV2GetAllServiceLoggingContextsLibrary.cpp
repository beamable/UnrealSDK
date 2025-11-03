
#include "BeamableCore/Public/AutoGen/BeamoV2GetAllServiceLoggingContextsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2GetAllServiceLoggingContextsLibrary::BeamoV2GetAllServiceLoggingContextsToJsonString(const UBeamoV2GetAllServiceLoggingContexts* Serializable, const bool Pretty)
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

UBeamoV2GetAllServiceLoggingContexts* UBeamoV2GetAllServiceLoggingContextsLibrary::Make(FOptionalArrayOfBeamoV2ServiceLoggingContext Contexts, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2GetAllServiceLoggingContexts>(Outer);
	Serializable->Contexts = Contexts;
	
	return Serializable;
}

void UBeamoV2GetAllServiceLoggingContextsLibrary::Break(const UBeamoV2GetAllServiceLoggingContexts* Serializable, FOptionalArrayOfBeamoV2ServiceLoggingContext& Contexts)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Contexts = Serializable->Contexts;
	}
		
}

