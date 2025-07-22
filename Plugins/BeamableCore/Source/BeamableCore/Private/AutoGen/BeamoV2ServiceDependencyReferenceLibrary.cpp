
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceDependencyReferenceLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ServiceDependencyReferenceLibrary::BeamoV2ServiceDependencyReferenceToJsonString(const UBeamoV2ServiceDependencyReference* Serializable, const bool Pretty)
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

UBeamoV2ServiceDependencyReference* UBeamoV2ServiceDependencyReferenceLibrary::Make(FOptionalString Id, FOptionalString StorageType, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ServiceDependencyReference>(Outer);
	Serializable->Id = Id;
	Serializable->StorageType = StorageType;
	
	return Serializable;
}

void UBeamoV2ServiceDependencyReferenceLibrary::Break(const UBeamoV2ServiceDependencyReference* Serializable, FOptionalString& Id, FOptionalString& StorageType)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		StorageType = Serializable->StorageType;
	}
		
}

