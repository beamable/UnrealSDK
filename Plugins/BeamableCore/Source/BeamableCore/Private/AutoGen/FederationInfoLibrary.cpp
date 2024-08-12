
#include "BeamableCore/Public/AutoGen/FederationInfoLibrary.h"

#include "CoreMinimal.h"


FString UFederationInfoLibrary::FederationInfoToJsonString(const UFederationInfo* Serializable, const bool Pretty)
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

UFederationInfo* UFederationInfoLibrary::Make(FString Service, FString Namespace, FOptionalOptionalJsonNodeWrapper Settings, UObject* Outer)
{
	auto Serializable = NewObject<UFederationInfo>(Outer);
	Serializable->Service = Service;
	Serializable->Namespace = Namespace;
	Serializable->Settings = Settings;
	
	return Serializable;
}

void UFederationInfoLibrary::Break(const UFederationInfo* Serializable, FString& Service, FString& Namespace, FOptionalOptionalJsonNodeWrapper& Settings)
{
	Service = Serializable->Service;
	Namespace = Serializable->Namespace;
	Settings = Serializable->Settings;
		
}

