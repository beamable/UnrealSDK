
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceComponentLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ServiceComponentLibrary::BeamoV2ServiceComponentToJsonString(const UBeamoV2ServiceComponent* Serializable, const bool Pretty)
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

UBeamoV2ServiceComponent* UBeamoV2ServiceComponentLibrary::Make(FOptionalString Name, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ServiceComponent>(Outer);
	Serializable->Name = Name;
	
	return Serializable;
}

void UBeamoV2ServiceComponentLibrary::Break(const UBeamoV2ServiceComponent* Serializable, FOptionalString& Name)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
	}
		
}

