
#include "BeamableCore/Public/AutoGen/JoinLobbyByPasscodeLibrary.h"

#include "CoreMinimal.h"


FString UJoinLobbyByPasscodeLibrary::JoinLobbyByPasscodeToJsonString(const UJoinLobbyByPasscode* Serializable, const bool Pretty)
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

UJoinLobbyByPasscode* UJoinLobbyByPasscodeLibrary::Make(FOptionalString Passcode, FOptionalArrayOfBeamTag Tags, UObject* Outer)
{
	auto Serializable = NewObject<UJoinLobbyByPasscode>(Outer);
	Serializable->Passcode = Passcode;
	Serializable->Tags = Tags;
	
	return Serializable;
}

void UJoinLobbyByPasscodeLibrary::Break(const UJoinLobbyByPasscode* Serializable, FOptionalString& Passcode, FOptionalArrayOfBeamTag& Tags)
{
	Passcode = Serializable->Passcode;
	Tags = Serializable->Tags;
		
}

