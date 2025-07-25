
#include "BeamableCore/Public/AutoGen/WebhookCometLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UWebhookCometLibrary::WebhookCometToJsonString(const UWebhookComet* Serializable, const bool Pretty)
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

UWebhookComet* UWebhookCometLibrary::Make(FString Method, URouteVariables* Variables, FString Symbol, UServiceRoute* Route, URouteParameters* Parameters, FOptionalString Description, UObject* Outer)
{
	auto Serializable = NewObject<UWebhookComet>(Outer);
	Serializable->Method = Method;
	Serializable->Variables = Variables;
	Serializable->Symbol = Symbol;
	Serializable->Route = Route;
	Serializable->Parameters = Parameters;
	Serializable->Description = Description;
	
	return Serializable;
}

void UWebhookCometLibrary::Break(const UWebhookComet* Serializable, FString& Method, URouteVariables*& Variables, FString& Symbol, UServiceRoute*& Route, URouteParameters*& Parameters, FOptionalString& Description)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Method = Serializable->Method;
		Variables = Serializable->Variables;
		Symbol = Serializable->Symbol;
		Route = Serializable->Route;
		Parameters = Serializable->Parameters;
		Description = Serializable->Description;
	}
		
}

