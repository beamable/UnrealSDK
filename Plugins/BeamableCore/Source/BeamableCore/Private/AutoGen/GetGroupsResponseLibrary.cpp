
#include "BeamableCore/Public/AutoGen/GetGroupsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetGroupsResponseLibrary::GetGroupsResponseToJsonString(const UGetGroupsResponse* Serializable, const bool Pretty)
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

UGetGroupsResponse* UGetGroupsResponseLibrary::Make(TArray<UTournamentGroupEntry*> Entries, FOptionalTournamentGroupEntry Focus, UObject* Outer)
{
	auto Serializable = NewObject<UGetGroupsResponse>(Outer);
	Serializable->Entries = Entries;
	Serializable->Focus = Focus;
	
	return Serializable;
}

void UGetGroupsResponseLibrary::Break(const UGetGroupsResponse* Serializable, TArray<UTournamentGroupEntry*>& Entries, FOptionalTournamentGroupEntry& Focus)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Entries = Serializable->Entries;
		Focus = Serializable->Focus;
	}
		
}

