
#include "AutoGen/DeleteRoleRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UDeleteRoleRequestBodyLibrary::DeleteRoleRequestBodyToJsonString(const UDeleteRoleRequestBody* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UDeleteRoleRequestBody* UDeleteRoleRequestBodyLibrary::Make(FString Realm, FString Role, UObject* Outer)
{
	auto Serializable = NewObject<UDeleteRoleRequestBody>(Outer);
	Serializable->Realm = Realm;
	Serializable->Role = Role;
	
	return Serializable;
}

void UDeleteRoleRequestBodyLibrary::Break(const UDeleteRoleRequestBody* Serializable, FString& Realm, FString& Role)
{
	Realm = Serializable->Realm;
	Role = Serializable->Role;
		
}

