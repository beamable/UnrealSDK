
#include "BeamableCore/Public/AutoGen/SupportedFederationLibrary.h"

#include "CoreMinimal.h"


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

USupportedFederation* USupportedFederationLibrary::Make(EFederationType Type, FOptionalString NameSpace, UObject* Outer)
{
	auto Serializable = NewObject<USupportedFederation>(Outer);
	Serializable->Type = Type;
	Serializable->NameSpace = NameSpace;
	
	return Serializable;
}

void USupportedFederationLibrary::Break(const USupportedFederation* Serializable, EFederationType& Type, FOptionalString& NameSpace)
{
	Type = Serializable->Type;
	NameSpace = Serializable->NameSpace;
		
}

