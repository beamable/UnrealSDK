
#include "BeamableCore/Public/AutoGen/ApiPartiesMembersDeletePartyResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UApiPartiesMembersDeletePartyResponseLibrary::ApiPartiesMembersDeletePartyResponseToJsonString(const UApiPartiesMembersDeletePartyResponse* Serializable, const bool Pretty)
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

UApiPartiesMembersDeletePartyResponse* UApiPartiesMembersDeletePartyResponseLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UApiPartiesMembersDeletePartyResponse>(Outer);
	
	return Serializable;
}



