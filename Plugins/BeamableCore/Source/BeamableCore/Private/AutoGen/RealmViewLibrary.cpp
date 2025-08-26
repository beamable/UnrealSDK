
#include "BeamableCore/Public/AutoGen/RealmViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmViewLibrary::RealmViewToJsonString(const URealmView* Serializable, const bool Pretty)
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

URealmView* URealmViewLibrary::Make(FString DisplayName, FString RealmId, FOptionalBool bArchived, FOptionalBool bSharded, FOptionalString CustomerId, FOptionalString Parent, FOptionalString Secret, FOptionalArrayOfString Children, UObject* Outer)
{
	auto Serializable = NewObject<URealmView>(Outer);
	Serializable->DisplayName = DisplayName;
	Serializable->RealmId = RealmId;
	Serializable->bArchived = bArchived;
	Serializable->bSharded = bSharded;
	Serializable->CustomerId = CustomerId;
	Serializable->Parent = Parent;
	Serializable->Secret = Secret;
	Serializable->Children = Children;
	
	return Serializable;
}

void URealmViewLibrary::Break(const URealmView* Serializable, FString& DisplayName, FString& RealmId, FOptionalBool& bArchived, FOptionalBool& bSharded, FOptionalString& CustomerId, FOptionalString& Parent, FOptionalString& Secret, FOptionalArrayOfString& Children)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		DisplayName = Serializable->DisplayName;
		RealmId = Serializable->RealmId;
		bArchived = Serializable->bArchived;
		bSharded = Serializable->bSharded;
		CustomerId = Serializable->CustomerId;
		Parent = Serializable->Parent;
		Secret = Serializable->Secret;
		Children = Serializable->Children;
	}
		
}

