
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

URealm* URealmLibrary::Make(FString Name, FString Plan, FOptionalBool bIsArchived, FOptionalBool bSharded, FOptionalString Secret, FOptionalString DisplayName, FOptionalString Parent, FOptionalDateTime Created, FOptionalArrayOfString Children, FOptionalMapOfString Config, FOptionalMapOfString CustomCharts, UObject* Outer)
{
	auto Serializable = NewObject<URealm>(Outer);
	Serializable->Name = Name;
	Serializable->Plan = Plan;
	Serializable->bIsArchived = bIsArchived;
	Serializable->bSharded = bSharded;
	Serializable->Secret = Secret;
	Serializable->DisplayName = DisplayName;
	Serializable->Parent = Parent;
	Serializable->Created = Created;
	Serializable->Children = Children;
	Serializable->Config = Config;
	Serializable->CustomCharts = CustomCharts;
	
	return Serializable;
}

void URealmLibrary::Break(const URealm* Serializable, FString& Name, FString& Plan, FOptionalBool& bIsArchived, FOptionalBool& bSharded, FOptionalString& Secret, FOptionalString& DisplayName, FOptionalString& Parent, FOptionalDateTime& Created, FOptionalArrayOfString& Children, FOptionalMapOfString& Config, FOptionalMapOfString& CustomCharts)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Plan = Serializable->Plan;
		bIsArchived = Serializable->bIsArchived;
		bSharded = Serializable->bSharded;
		Secret = Serializable->Secret;
		DisplayName = Serializable->DisplayName;
		Parent = Serializable->Parent;
		Created = Serializable->Created;
		Children = Serializable->Children;
		Config = Serializable->Config;
		CustomCharts = Serializable->CustomCharts;
	}
		
}

