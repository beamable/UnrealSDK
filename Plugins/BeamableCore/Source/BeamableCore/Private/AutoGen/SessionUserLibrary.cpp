
#include "BeamableCore/Public/AutoGen/SessionUserLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USessionUserLibrary::SessionUserToJsonString(const USessionUser* Serializable, const bool Pretty)
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

USessionUser* USessionUserLibrary::Make(FString Name, FString Email, int64 GamerTag, FString Username, FString LastName, FString FirstName, int64 Id, FString Lang, FOptionalString Cid, FOptionalInt64 Heartbeat, FOptionalString Password, UObject* Outer)
{
	auto Serializable = NewObject<USessionUser>(Outer);
	Serializable->Name = Name;
	Serializable->Email = Email;
	Serializable->GamerTag = GamerTag;
	Serializable->Username = Username;
	Serializable->LastName = LastName;
	Serializable->FirstName = FirstName;
	Serializable->Id = Id;
	Serializable->Lang = Lang;
	Serializable->Cid = Cid;
	Serializable->Heartbeat = Heartbeat;
	Serializable->Password = Password;
	
	return Serializable;
}

void USessionUserLibrary::Break(const USessionUser* Serializable, FString& Name, FString& Email, int64& GamerTag, FString& Username, FString& LastName, FString& FirstName, int64& Id, FString& Lang, FOptionalString& Cid, FOptionalInt64& Heartbeat, FOptionalString& Password)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Email = Serializable->Email;
		GamerTag = Serializable->GamerTag;
		Username = Serializable->Username;
		LastName = Serializable->LastName;
		FirstName = Serializable->FirstName;
		Id = Serializable->Id;
		Lang = Serializable->Lang;
		Cid = Serializable->Cid;
		Heartbeat = Serializable->Heartbeat;
		Password = Serializable->Password;
	}
		
}

