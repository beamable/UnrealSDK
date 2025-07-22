
#include "BeamableCore/Public/AutoGen/BeamoV2SupportedFederationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2SupportedFederationLibrary::BeamoV2SupportedFederationToJsonString(const UBeamoV2SupportedFederation* Serializable, const bool Pretty)
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

UBeamoV2SupportedFederation* UBeamoV2SupportedFederationLibrary::Make(FOptionalBeamoV2FederationType Type, FOptionalString NameSpace, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2SupportedFederation>(Outer);
	Serializable->Type = Type;
	Serializable->NameSpace = NameSpace;
	
	return Serializable;
}

void UBeamoV2SupportedFederationLibrary::Break(const UBeamoV2SupportedFederation* Serializable, FOptionalBeamoV2FederationType& Type, FOptionalString& NameSpace)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Type = Serializable->Type;
		NameSpace = Serializable->NameSpace;
	}
		
}

