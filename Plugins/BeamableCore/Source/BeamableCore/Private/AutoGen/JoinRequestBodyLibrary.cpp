
#include "BeamableCore/Public/AutoGen/JoinRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UJoinRequestBodyLibrary::JoinRequestBodyToJsonString(const UJoinRequestBody* Serializable, const bool Pretty)
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

UJoinRequestBody* UJoinRequestBodyLibrary::Make(FString TournamentId, FOptionalString ContentId, UObject* Outer)
{
	auto Serializable = NewObject<UJoinRequestBody>(Outer);
	Serializable->TournamentId = TournamentId;
	Serializable->ContentId = ContentId;
	
	return Serializable;
}

void UJoinRequestBodyLibrary::Break(const UJoinRequestBody* Serializable, FString& TournamentId, FOptionalString& ContentId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		TournamentId = Serializable->TournamentId;
		ContentId = Serializable->ContentId;
	}
		
}

