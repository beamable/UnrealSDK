
#include "BeamableCore/Public/AutoGen/BeamoV2ProtoErrorLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ProtoErrorLibrary::BeamoV2ProtoErrorToJsonString(const UBeamoV2ProtoError* Serializable, const bool Pretty)
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

UBeamoV2ProtoError* UBeamoV2ProtoErrorLibrary::Make(FOptionalInt32 Status, FOptionalString Error, FOptionalString Description, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ProtoError>(Outer);
	Serializable->Status = Status;
	Serializable->Error = Error;
	Serializable->Description = Description;
	
	return Serializable;
}

void UBeamoV2ProtoErrorLibrary::Break(const UBeamoV2ProtoError* Serializable, FOptionalInt32& Status, FOptionalString& Error, FOptionalString& Description)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Status = Serializable->Status;
		Error = Serializable->Error;
		Description = Serializable->Description;
	}
		
}

