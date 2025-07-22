
#include "BeamableCore/Public/AutoGen/GetElasticContainerRegistryURILibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetElasticContainerRegistryURILibrary::GetElasticContainerRegistryURIToJsonString(const UGetElasticContainerRegistryURI* Serializable, const bool Pretty)
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

UGetElasticContainerRegistryURI* UGetElasticContainerRegistryURILibrary::Make(FString Uri, UObject* Outer)
{
	auto Serializable = NewObject<UGetElasticContainerRegistryURI>(Outer);
	Serializable->Uri = Uri;
	
	return Serializable;
}

void UGetElasticContainerRegistryURILibrary::Break(const UGetElasticContainerRegistryURI* Serializable, FString& Uri)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Uri = Serializable->Uri;
	}
		
}

