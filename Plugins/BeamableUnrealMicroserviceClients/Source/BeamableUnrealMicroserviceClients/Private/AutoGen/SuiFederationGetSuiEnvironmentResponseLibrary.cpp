
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SuiFederationGetSuiEnvironmentResponseLibrary.h"

#include "CoreMinimal.h"


FString USuiFederationGetSuiEnvironmentResponseLibrary::SuiFederationGetSuiEnvironmentResponseToJsonString(const USuiFederationGetSuiEnvironmentResponse* Serializable, const bool Pretty)
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

USuiFederationGetSuiEnvironmentResponse* USuiFederationGetSuiEnvironmentResponseLibrary::Make(FString Value, UObject* Outer)
{
	auto Serializable = NewObject<USuiFederationGetSuiEnvironmentResponse>(Outer);
	Serializable->Value = Value;
	
	return Serializable;
}

void USuiFederationGetSuiEnvironmentResponseLibrary::Break(const USuiFederationGetSuiEnvironmentResponse* Serializable, FString& Value)
{
	Value = Serializable->Value;
		
}

