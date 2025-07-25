
#include "BeamableCore/Public/AutoGen/UpdateRoleLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUpdateRoleLibrary::UpdateRoleToJsonString(const UUpdateRole* Serializable, const bool Pretty)
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

UUpdateRole* UUpdateRoleLibrary::Make(FOptionalBeamCid Cid, FOptionalBeamPid Realm, FOptionalString Role, UObject* Outer)
{
	auto Serializable = NewObject<UUpdateRole>(Outer);
	Serializable->Cid = Cid;
	Serializable->Realm = Realm;
	Serializable->Role = Role;
	
	return Serializable;
}

void UUpdateRoleLibrary::Break(const UUpdateRole* Serializable, FOptionalBeamCid& Cid, FOptionalBeamPid& Realm, FOptionalString& Role)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Cid = Serializable->Cid;
		Realm = Serializable->Realm;
		Role = Serializable->Role;
	}
		
}

