
#include "BeamableCore/Public/AutoGen/BeamoV2PASlowQueryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2PASlowQueryLibrary::BeamoV2PASlowQueryToJsonString(const UBeamoV2PASlowQuery* Serializable, const bool Pretty)
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

UBeamoV2PASlowQuery* UBeamoV2PASlowQueryLibrary::Make(FString Line, FString Namespace, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2PASlowQuery>(Outer);
	Serializable->Line = Line;
	Serializable->Namespace = Namespace;
	
	return Serializable;
}

void UBeamoV2PASlowQueryLibrary::Break(const UBeamoV2PASlowQuery* Serializable, FString& Line, FString& Namespace)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Line = Serializable->Line;
		Namespace = Serializable->Namespace;
	}
		
}

