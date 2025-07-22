
#include "BeamableCore/Public/AutoGen/DeleteRoleRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDeleteRoleRequestBodyLibrary::DeleteRoleRequestBodyToJsonString(const UDeleteRoleRequestBody* Serializable, const bool Pretty)
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

UDeleteRoleRequestBody* UDeleteRoleRequestBodyLibrary::Make(FOptionalBeamPid Realm, FOptionalString Role, UObject* Outer)
{
	auto Serializable = NewObject<UDeleteRoleRequestBody>(Outer);
	Serializable->Realm = Realm;
	Serializable->Role = Role;
	
	return Serializable;
}

void UDeleteRoleRequestBodyLibrary::Break(const UDeleteRoleRequestBody* Serializable, FOptionalBeamPid& Realm, FOptionalString& Role)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Realm = Serializable->Realm;
		Role = Serializable->Role;
	}
		
}

