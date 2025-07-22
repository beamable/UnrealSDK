
#include "BeamableCore/Public/AutoGen/BeamoBasicReferenceLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoBasicReferenceLibrary::BeamoBasicReferenceToJsonString(const UBeamoBasicReference* Serializable, const bool Pretty)
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

UBeamoBasicReference* UBeamoBasicReferenceLibrary::Make(bool bArchived, bool bArm, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoBasicReference>(Outer);
	Serializable->bArchived = bArchived;
	Serializable->bArm = bArm;
	
	return Serializable;
}

void UBeamoBasicReferenceLibrary::Break(const UBeamoBasicReference* Serializable, bool& bArchived, bool& bArm)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bArchived = Serializable->bArchived;
		bArm = Serializable->bArm;
	}
		
}

