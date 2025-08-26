
#include "BeamableCore/Public/AutoGen/RewardsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URewardsRequestBodyLibrary::RewardsRequestBodyToJsonString(const URewardsRequestBody* Serializable, const bool Pretty)
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

URewardsRequestBody* URewardsRequestBodyLibrary::Make(FOptionalString TournamentId, FOptionalString ContentId, UObject* Outer)
{
	auto Serializable = NewObject<URewardsRequestBody>(Outer);
	Serializable->TournamentId = TournamentId;
	Serializable->ContentId = ContentId;
	
	return Serializable;
}

void URewardsRequestBodyLibrary::Break(const URewardsRequestBody* Serializable, FOptionalString& TournamentId, FOptionalString& ContentId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		TournamentId = Serializable->TournamentId;
		ContentId = Serializable->ContentId;
	}
		
}

