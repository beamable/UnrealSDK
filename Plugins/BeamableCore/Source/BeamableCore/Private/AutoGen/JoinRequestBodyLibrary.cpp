
#include "BeamableCore/Public/AutoGen/JoinRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UJoinRequestBodyLibrary::JoinRequestBodyToJsonString(const UJoinRequestBody* Serializable, const bool Pretty)
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

UJoinRequestBody* UJoinRequestBodyLibrary::Make(FString TournamentId, UObject* Outer)
{
	auto Serializable = NewObject<UJoinRequestBody>(Outer);
	Serializable->TournamentId = TournamentId;
	
	return Serializable;
}

void UJoinRequestBodyLibrary::Break(const UJoinRequestBody* Serializable, FString& TournamentId)
{
	TournamentId = Serializable->TournamentId;
		
}

