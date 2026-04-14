
#include "BeamableCore/Public/AutoGen/RoleAssociationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URoleAssociationLibrary::RoleAssociationToJsonString(const URoleAssociation* Serializable, const bool Pretty)
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

URoleAssociation* URoleAssociationLibrary::Make(FOptionalString RealmId, FOptionalString RoleString, UObject* Outer)
{
	auto Serializable = NewObject<URoleAssociation>(Outer);
	Serializable->RealmId = RealmId;
	Serializable->RoleString = RoleString;
	
	return Serializable;
}

void URoleAssociationLibrary::Break(const URoleAssociation* Serializable, FOptionalString& RealmId, FOptionalString& RoleString)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		RealmId = Serializable->RealmId;
		RoleString = Serializable->RoleString;
	}
		
}

