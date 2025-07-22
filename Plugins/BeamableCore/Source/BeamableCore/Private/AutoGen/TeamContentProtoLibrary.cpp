
#include "BeamableCore/Public/AutoGen/TeamContentProtoLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTeamContentProtoLibrary::TeamContentProtoToJsonString(const UTeamContentProto* Serializable, const bool Pretty)
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

UTeamContentProto* UTeamContentProtoLibrary::Make(FOptionalString Name, FOptionalInt32 MaxPlayers, FOptionalInt32 MinPlayers, UObject* Outer)
{
	auto Serializable = NewObject<UTeamContentProto>(Outer);
	Serializable->Name = Name;
	Serializable->MaxPlayers = MaxPlayers;
	Serializable->MinPlayers = MinPlayers;
	
	return Serializable;
}

void UTeamContentProtoLibrary::Break(const UTeamContentProto* Serializable, FOptionalString& Name, FOptionalInt32& MaxPlayers, FOptionalInt32& MinPlayers)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		MaxPlayers = Serializable->MaxPlayers;
		MinPlayers = Serializable->MinPlayers;
	}
		
}

