
#include "BeamableCore/Public/AutoGen/PromoteNewLeaderLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPromoteNewLeaderLibrary::PromoteNewLeaderToJsonString(const UPromoteNewLeader* Serializable, const bool Pretty)
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

UPromoteNewLeader* UPromoteNewLeaderLibrary::Make(FOptionalBeamGamerTag PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<UPromoteNewLeader>(Outer);
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void UPromoteNewLeaderLibrary::Break(const UPromoteNewLeader* Serializable, FOptionalBeamGamerTag& PlayerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
	}
		
}

