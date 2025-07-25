
#include "BeamableCore/Public/AutoGen/ApiBeamoOtelViewsDeleteBeamoOtelResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UApiBeamoOtelViewsDeleteBeamoOtelResponseLibrary::ApiBeamoOtelViewsDeleteBeamoOtelResponseToJsonString(const UApiBeamoOtelViewsDeleteBeamoOtelResponse* Serializable, const bool Pretty)
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

UApiBeamoOtelViewsDeleteBeamoOtelResponse* UApiBeamoOtelViewsDeleteBeamoOtelResponseLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UApiBeamoOtelViewsDeleteBeamoOtelResponse>(Outer);
	
	return Serializable;
}



