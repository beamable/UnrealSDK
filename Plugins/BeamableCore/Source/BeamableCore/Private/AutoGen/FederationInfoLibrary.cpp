
#include "BeamableCore/Public/AutoGen/FederationInfoLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


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

UFederationInfo* UFederationInfoLibrary::Make(FString Service, FString Namespace, UObject* Outer)
{
	auto Serializable = NewObject<UFederationInfo>(Outer);
	Serializable->Service = Service;
	Serializable->Namespace = Namespace;
	
	return Serializable;
}

void UFederationInfoLibrary::Break(const UFederationInfo* Serializable, FString& Service, FString& Namespace)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Service = Serializable->Service;
		Namespace = Serializable->Namespace;
	}
		
}

