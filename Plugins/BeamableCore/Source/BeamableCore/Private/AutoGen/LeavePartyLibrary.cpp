
#include "BeamableCore/Public/AutoGen/LeavePartyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeavePartyLibrary::LeavePartyToJsonString(const ULeaveParty* Serializable, const bool Pretty)
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

ULeaveParty* ULeavePartyLibrary::Make(FOptionalBeamGamerTag PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<ULeaveParty>(Outer);
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void ULeavePartyLibrary::Break(const ULeaveParty* Serializable, FOptionalBeamGamerTag& PlayerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
	}
		
}

