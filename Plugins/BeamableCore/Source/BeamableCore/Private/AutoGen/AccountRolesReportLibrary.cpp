
#include "BeamableCore/Public/AutoGen/AccountRolesReportLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAccountRolesReportLibrary::AccountRolesReportToJsonString(const UAccountRolesReport* Serializable, const bool Pretty)
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

UAccountRolesReport* UAccountRolesReportLibrary::Make(int64 AccountId, FString Email, TArray<URealmRolesReport*> Realms, UObject* Outer)
{
	auto Serializable = NewObject<UAccountRolesReport>(Outer);
	Serializable->AccountId = AccountId;
	Serializable->Email = Email;
	Serializable->Realms = Realms;
	
	return Serializable;
}

void UAccountRolesReportLibrary::Break(const UAccountRolesReport* Serializable, int64& AccountId, FString& Email, TArray<URealmRolesReport*>& Realms)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		AccountId = Serializable->AccountId;
		Email = Serializable->Email;
		Realms = Serializable->Realms;
	}
		
}

