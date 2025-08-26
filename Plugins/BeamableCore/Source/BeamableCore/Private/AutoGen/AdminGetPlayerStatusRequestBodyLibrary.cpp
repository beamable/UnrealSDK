
#include "BeamableCore/Public/AutoGen/AdminGetPlayerStatusRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAdminGetPlayerStatusRequestBodyLibrary::AdminGetPlayerStatusRequestBodyToJsonString(const UAdminGetPlayerStatusRequestBody* Serializable, const bool Pretty)
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

UAdminGetPlayerStatusRequestBody* UAdminGetPlayerStatusRequestBodyLibrary::Make(int64 PlayerId, FOptionalBool bHasUnclaimedRewards, FOptionalString TournamentId, FOptionalString ContentId, UObject* Outer)
{
	auto Serializable = NewObject<UAdminGetPlayerStatusRequestBody>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->bHasUnclaimedRewards = bHasUnclaimedRewards;
	Serializable->TournamentId = TournamentId;
	Serializable->ContentId = ContentId;
	
	return Serializable;
}

void UAdminGetPlayerStatusRequestBodyLibrary::Break(const UAdminGetPlayerStatusRequestBody* Serializable, int64& PlayerId, FOptionalBool& bHasUnclaimedRewards, FOptionalString& TournamentId, FOptionalString& ContentId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		bHasUnclaimedRewards = Serializable->bHasUnclaimedRewards;
		TournamentId = Serializable->TournamentId;
		ContentId = Serializable->ContentId;
	}
		
}

