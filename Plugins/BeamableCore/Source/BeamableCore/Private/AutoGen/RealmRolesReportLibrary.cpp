
#include "BeamableCore/Public/AutoGen/RealmRolesReportLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmRolesReportLibrary::RealmRolesReportToJsonString(const URealmRolesReport* Serializable, const bool Pretty)
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

URealmRolesReport* URealmRolesReportLibrary::Make(FString RealmName, FString RealmDisplayName, TArray<FString> Roles, UObject* Outer)
{
	auto Serializable = NewObject<URealmRolesReport>(Outer);
	Serializable->RealmName = RealmName;
	Serializable->RealmDisplayName = RealmDisplayName;
	Serializable->Roles = Roles;
	
	return Serializable;
}

void URealmRolesReportLibrary::Break(const URealmRolesReport* Serializable, FString& RealmName, FString& RealmDisplayName, TArray<FString>& Roles)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		RealmName = Serializable->RealmName;
		RealmDisplayName = Serializable->RealmDisplayName;
		Roles = Serializable->Roles;
	}
		
}

