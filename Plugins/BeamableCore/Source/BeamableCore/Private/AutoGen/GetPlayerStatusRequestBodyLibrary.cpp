
#include "BeamableCore/Public/AutoGen/GetPlayerStatusRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetPlayerStatusRequestBodyLibrary::GetPlayerStatusRequestBodyToJsonString(const UGetPlayerStatusRequestBody* Serializable, const bool Pretty)
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

UGetPlayerStatusRequestBody* UGetPlayerStatusRequestBodyLibrary::Make(FOptionalBool bHasUnclaimedRewards, FOptionalString ContentId, FOptionalString TournamentId, UObject* Outer)
{
	auto Serializable = NewObject<UGetPlayerStatusRequestBody>(Outer);
	Serializable->bHasUnclaimedRewards = bHasUnclaimedRewards;
	Serializable->ContentId = ContentId;
	Serializable->TournamentId = TournamentId;
	
	return Serializable;
}

void UGetPlayerStatusRequestBodyLibrary::Break(const UGetPlayerStatusRequestBody* Serializable, FOptionalBool& bHasUnclaimedRewards, FOptionalString& ContentId, FOptionalString& TournamentId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bHasUnclaimedRewards = Serializable->bHasUnclaimedRewards;
		ContentId = Serializable->ContentId;
		TournamentId = Serializable->TournamentId;
	}
		
}

