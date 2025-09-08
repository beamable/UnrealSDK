
#include "BeamableCore/Public/AutoGen/RealmAssociationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmAssociationLibrary::RealmAssociationToJsonString(const URealmAssociation* Serializable, const bool Pretty)
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

URealmAssociation* URealmAssociationLibrary::Make(FOptionalString RealmId, FOptionalInt64 PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<URealmAssociation>(Outer);
	Serializable->RealmId = RealmId;
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void URealmAssociationLibrary::Break(const URealmAssociation* Serializable, FOptionalString& RealmId, FOptionalInt64& PlayerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		RealmId = Serializable->RealmId;
		PlayerId = Serializable->PlayerId;
	}
		
}

