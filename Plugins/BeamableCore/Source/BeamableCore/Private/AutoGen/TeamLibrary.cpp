
#include "BeamableCore/Public/AutoGen/TeamLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTeamLibrary::TeamToJsonString(const UTeam* Serializable, const bool Pretty)
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

UTeam* UTeamLibrary::Make(FOptionalString Name, FOptionalArrayOfBeamGamerTag Players, UObject* Outer)
{
	auto Serializable = NewObject<UTeam>(Outer);
	Serializable->Name = Name;
	Serializable->Players = Players;
	
	return Serializable;
}

void UTeamLibrary::Break(const UTeam* Serializable, FOptionalString& Name, FOptionalArrayOfBeamGamerTag& Players)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Players = Serializable->Players;
	}
		
}

