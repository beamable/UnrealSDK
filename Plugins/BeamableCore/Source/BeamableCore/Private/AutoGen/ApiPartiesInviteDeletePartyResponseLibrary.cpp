
#include "BeamableCore/Public/AutoGen/ApiPartiesInviteDeletePartyResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UApiPartiesInviteDeletePartyResponseLibrary::ApiPartiesInviteDeletePartyResponseToJsonString(const UApiPartiesInviteDeletePartyResponse* Serializable, const bool Pretty)
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

UApiPartiesInviteDeletePartyResponse* UApiPartiesInviteDeletePartyResponseLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UApiPartiesInviteDeletePartyResponse>(Outer);
	
	return Serializable;
}



