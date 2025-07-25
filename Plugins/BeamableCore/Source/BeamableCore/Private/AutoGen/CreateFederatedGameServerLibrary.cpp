
#include "BeamableCore/Public/AutoGen/CreateFederatedGameServerLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCreateFederatedGameServerLibrary::CreateFederatedGameServerToJsonString(const UCreateFederatedGameServer* Serializable, const bool Pretty)
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

UCreateFederatedGameServer* UCreateFederatedGameServerLibrary::Make(FOptionalBeamContentId MatchType, UObject* Outer)
{
	auto Serializable = NewObject<UCreateFederatedGameServer>(Outer);
	Serializable->MatchType = MatchType;
	
	return Serializable;
}

void UCreateFederatedGameServerLibrary::Break(const UCreateFederatedGameServer* Serializable, FOptionalBeamContentId& MatchType)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		MatchType = Serializable->MatchType;
	}
		
}

