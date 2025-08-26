
#include "BeamableCore/Public/AutoGen/ApiPlayersPartiesDeletePlayerPartyResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UApiPlayersPartiesDeletePlayerPartyResponseLibrary::ApiPlayersPartiesDeletePlayerPartyResponseToJsonString(const UApiPlayersPartiesDeletePlayerPartyResponse* Serializable, const bool Pretty)
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

UApiPlayersPartiesDeletePlayerPartyResponse* UApiPlayersPartiesDeletePlayerPartyResponseLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UApiPlayersPartiesDeletePlayerPartyResponse>(Outer);
	
	return Serializable;
}



