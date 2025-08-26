
#include "BeamableCore/Public/AutoGen/ItemArchetypeLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UItemArchetypeLibrary::ItemArchetypeToJsonString(const UItemArchetype* Serializable, const bool Pretty)
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

UItemArchetype* UItemArchetypeLibrary::Make(FString Symbol, FOptionalFederationInfo External, FOptionalBeamClientPermission ClientPermission, UObject* Outer)
{
	auto Serializable = NewObject<UItemArchetype>(Outer);
	Serializable->Symbol = Symbol;
	Serializable->External = External;
	Serializable->ClientPermission = ClientPermission;
	
	return Serializable;
}

void UItemArchetypeLibrary::Break(const UItemArchetype* Serializable, FString& Symbol, FOptionalFederationInfo& External, FOptionalBeamClientPermission& ClientPermission)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Symbol = Serializable->Symbol;
		External = Serializable->External;
		ClientPermission = Serializable->ClientPermission;
	}
		
}

