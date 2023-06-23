
#include "BeamableCore/Public/AutoGen/LeavePartyLibrary.h"

#include "CoreMinimal.h"


FString ULeavePartyLibrary::LeavePartyToJsonString(const ULeaveParty* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

ULeaveParty* ULeavePartyLibrary::Make(FOptionalString PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<ULeaveParty>(Outer);
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void ULeavePartyLibrary::Break(const ULeaveParty* Serializable, FOptionalString& PlayerId)
{
	PlayerId = Serializable->PlayerId;
		
}

