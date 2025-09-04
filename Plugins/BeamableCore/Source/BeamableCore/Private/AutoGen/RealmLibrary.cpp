
#include "BeamableCore/Public/AutoGen/RealmLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmLibrary::RealmToJsonString(const URealm* Serializable, const bool Pretty)
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

URealm* URealmLibrary::Make(FOptionalBool bIsArchived, FOptionalBool bSharded, FOptionalString Name, FOptionalString Secret, FOptionalString Plan, FOptionalString DisplayName, FOptionalString Parent, FOptionalArrayOfString Children, FOptionalMapOfString Config, UObject* Outer)
{
	auto Serializable = NewObject<URealm>(Outer);
	Serializable->bIsArchived = bIsArchived;
	Serializable->bSharded = bSharded;
	Serializable->Name = Name;
	Serializable->Secret = Secret;
	Serializable->Plan = Plan;
	Serializable->DisplayName = DisplayName;
	Serializable->Parent = Parent;
	Serializable->Children = Children;
	Serializable->Config = Config;
	
	return Serializable;
}

void URealmLibrary::Break(const URealm* Serializable, FOptionalBool& bIsArchived, FOptionalBool& bSharded, FOptionalString& Name, FOptionalString& Secret, FOptionalString& Plan, FOptionalString& DisplayName, FOptionalString& Parent, FOptionalArrayOfString& Children, FOptionalMapOfString& Config)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bIsArchived = Serializable->bIsArchived;
		bSharded = Serializable->bSharded;
		Name = Serializable->Name;
		Secret = Serializable->Secret;
		Plan = Serializable->Plan;
		DisplayName = Serializable->DisplayName;
		Parent = Serializable->Parent;
		Children = Serializable->Children;
		Config = Serializable->Config;
	}
		
}

