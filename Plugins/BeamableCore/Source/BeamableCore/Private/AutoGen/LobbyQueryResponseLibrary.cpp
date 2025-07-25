
#include "BeamableCore/Public/AutoGen/LobbyQueryResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULobbyQueryResponseLibrary::LobbyQueryResponseToJsonString(const ULobbyQueryResponse* Serializable, const bool Pretty)
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

ULobbyQueryResponse* ULobbyQueryResponseLibrary::Make(FOptionalArrayOfLobby Results, UObject* Outer)
{
	auto Serializable = NewObject<ULobbyQueryResponse>(Outer);
	Serializable->Results = Results;
	
	return Serializable;
}

void ULobbyQueryResponseLibrary::Break(const ULobbyQueryResponse* Serializable, FOptionalArrayOfLobby& Results)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Results = Serializable->Results;
	}
		
}

