
#include "BeamableCore/Public/AutoGen/SupportedFederationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USupportedFederationLibrary::SupportedFederationToJsonString(const USupportedFederation* Serializable, const bool Pretty)
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

USupportedFederation* USupportedFederationLibrary::Make(EBeamFederationType Type, FOptionalString NameSpace, UObject* Outer)
{
	auto Serializable = NewObject<USupportedFederation>(Outer);
	Serializable->Type = Type;
	Serializable->NameSpace = NameSpace;
	
	return Serializable;
}

void USupportedFederationLibrary::Break(const USupportedFederation* Serializable, EBeamFederationType& Type, FOptionalString& NameSpace)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Type = Serializable->Type;
		NameSpace = Serializable->NameSpace;
	}
		
}

