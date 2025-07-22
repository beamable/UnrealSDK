
#include "BeamableCore/Public/AutoGen/PlayerIdLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPlayerIdLibrary::PlayerIdToJsonString(const UPlayerId* Serializable, const bool Pretty)
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

UPlayerId* UPlayerIdLibrary::Make(FBeamGamerTag PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<UPlayerId>(Outer);
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void UPlayerIdLibrary::Break(const UPlayerId* Serializable, FBeamGamerTag& PlayerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
	}
		
}

