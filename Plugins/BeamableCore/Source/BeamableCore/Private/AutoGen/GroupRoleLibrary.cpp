
#include "BeamableCore/Public/AutoGen/GroupRoleLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGroupRoleLibrary::GroupRoleToJsonString(const UGroupRole* Serializable, const bool Pretty)
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

UGroupRole* UGroupRoleLibrary::Make(FString Name, TArray<FString> Permissions, UObject* Outer)
{
	auto Serializable = NewObject<UGroupRole>(Outer);
	Serializable->Name = Name;
	Serializable->Permissions = Permissions;
	
	return Serializable;
}

void UGroupRoleLibrary::Break(const UGroupRole* Serializable, FString& Name, TArray<FString>& Permissions)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Permissions = Serializable->Permissions;
	}
		
}

