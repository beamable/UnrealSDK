
#include "BeamableCore/Public/AutoGen/MicroserviceSecretResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMicroserviceSecretResponseLibrary::MicroserviceSecretResponseToJsonString(const UMicroserviceSecretResponse* Serializable, const bool Pretty)
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

UMicroserviceSecretResponse* UMicroserviceSecretResponseLibrary::Make(FString Secret, UObject* Outer)
{
	auto Serializable = NewObject<UMicroserviceSecretResponse>(Outer);
	Serializable->Secret = Secret;
	
	return Serializable;
}

void UMicroserviceSecretResponseLibrary::Break(const UMicroserviceSecretResponse* Serializable, FString& Secret)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Secret = Serializable->Secret;
	}
		
}

