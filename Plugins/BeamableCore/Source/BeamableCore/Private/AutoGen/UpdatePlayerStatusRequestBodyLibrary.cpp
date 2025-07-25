
#include "BeamableCore/Public/AutoGen/UpdatePlayerStatusRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUpdatePlayerStatusRequestBodyLibrary::UpdatePlayerStatusRequestBodyToJsonString(const UUpdatePlayerStatusRequestBody* Serializable, const bool Pretty)
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

UUpdatePlayerStatusRequestBody* UUpdatePlayerStatusRequestBodyLibrary::Make(int64 PlayerId, FString TournamentId, UPlayerStatusUpdate* Update, UObject* Outer)
{
	auto Serializable = NewObject<UUpdatePlayerStatusRequestBody>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->TournamentId = TournamentId;
	Serializable->Update = Update;
	
	return Serializable;
}

void UUpdatePlayerStatusRequestBodyLibrary::Break(const UUpdatePlayerStatusRequestBody* Serializable, int64& PlayerId, FString& TournamentId, UPlayerStatusUpdate*& Update)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		TournamentId = Serializable->TournamentId;
		Update = Serializable->Update;
	}
		
}

