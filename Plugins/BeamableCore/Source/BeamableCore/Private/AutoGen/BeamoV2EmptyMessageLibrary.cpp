
#include "BeamableCore/Public/AutoGen/BeamoV2EmptyMessageLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2EmptyMessageLibrary::BeamoV2EmptyMessageToJsonString(const UBeamoV2EmptyMessage* Serializable, const bool Pretty)
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

UBeamoV2EmptyMessage* UBeamoV2EmptyMessageLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2EmptyMessage>(Outer);
	
	return Serializable;
}



