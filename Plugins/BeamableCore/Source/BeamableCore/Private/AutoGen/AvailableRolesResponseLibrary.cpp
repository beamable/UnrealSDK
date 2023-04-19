
#include "BeamableCore/Public/AutoGen/AvailableRolesResponseLibrary.h"

#include "CoreMinimal.h"


FString UAvailableRolesResponseLibrary::AvailableRolesResponseToJsonString(const UAvailableRolesResponse* Serializable, const bool Pretty)
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

UAvailableRolesResponse* UAvailableRolesResponseLibrary::Make(TArray<FString> Roles, UObject* Outer)
{
	auto Serializable = NewObject<UAvailableRolesResponse>(Outer);
	Serializable->Roles = Roles;
	
	return Serializable;
}

void UAvailableRolesResponseLibrary::Break(const UAvailableRolesResponse* Serializable, TArray<FString>& Roles)
{
	Roles = Serializable->Roles;
		
}

