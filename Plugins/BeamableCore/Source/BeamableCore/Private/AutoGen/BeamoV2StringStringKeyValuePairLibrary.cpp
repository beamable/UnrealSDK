
#include "BeamableCore/Public/AutoGen/BeamoV2StringStringKeyValuePairLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2StringStringKeyValuePairLibrary::BeamoV2StringStringKeyValuePairToJsonString(const UBeamoV2StringStringKeyValuePair* Serializable, const bool Pretty)
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

UBeamoV2StringStringKeyValuePair* UBeamoV2StringStringKeyValuePairLibrary::Make(FOptionalString Key, FOptionalString Value, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2StringStringKeyValuePair>(Outer);
	Serializable->Key = Key;
	Serializable->Value = Value;
	
	return Serializable;
}

void UBeamoV2StringStringKeyValuePairLibrary::Break(const UBeamoV2StringStringKeyValuePair* Serializable, FOptionalString& Key, FOptionalString& Value)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Key = Serializable->Key;
		Value = Serializable->Value;
	}
		
}

