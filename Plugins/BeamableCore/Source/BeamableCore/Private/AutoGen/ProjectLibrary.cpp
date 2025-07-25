
#include "BeamableCore/Public/AutoGen/ProjectLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UProjectLibrary::ProjectToJsonString(const UProject* Serializable, const bool Pretty)
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

UProject* UProjectLibrary::Make(bool bArchived, bool bRoot, FString Secret, FBeamPid Name, FString Plan, TMap<FString, FString> CustomCharts, FOptionalBool bSharded, FOptionalBool bSigval, FOptionalString DisplayName, FOptionalString Parent, FOptionalString Status, FOptionalInt64 Created, FOptionalArrayOfString Children, FOptionalMapOfString Config, UObject* Outer)
{
	auto Serializable = NewObject<UProject>(Outer);
	Serializable->bArchived = bArchived;
	Serializable->bRoot = bRoot;
	Serializable->Secret = Secret;
	Serializable->Name = Name;
	Serializable->Plan = Plan;
	Serializable->CustomCharts = CustomCharts;
	Serializable->bSharded = bSharded;
	Serializable->bSigval = bSigval;
	Serializable->DisplayName = DisplayName;
	Serializable->Parent = Parent;
	Serializable->Status = Status;
	Serializable->Created = Created;
	Serializable->Children = Children;
	Serializable->Config = Config;
	
	return Serializable;
}

void UProjectLibrary::Break(const UProject* Serializable, bool& bArchived, bool& bRoot, FString& Secret, FBeamPid& Name, FString& Plan, TMap<FString, FString>& CustomCharts, FOptionalBool& bSharded, FOptionalBool& bSigval, FOptionalString& DisplayName, FOptionalString& Parent, FOptionalString& Status, FOptionalInt64& Created, FOptionalArrayOfString& Children, FOptionalMapOfString& Config)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bArchived = Serializable->bArchived;
		bRoot = Serializable->bRoot;
		Secret = Serializable->Secret;
		Name = Serializable->Name;
		Plan = Serializable->Plan;
		CustomCharts = Serializable->CustomCharts;
		bSharded = Serializable->bSharded;
		bSigval = Serializable->bSigval;
		DisplayName = Serializable->DisplayName;
		Parent = Serializable->Parent;
		Status = Serializable->Status;
		Created = Serializable->Created;
		Children = Serializable->Children;
		Config = Serializable->Config;
	}
		
}

