
#include "BeamableCore/Public/AutoGen/RouteParametersLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URouteParametersLibrary::RouteParametersToJsonString(const URouteParameters* Serializable, const bool Pretty)
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

URouteParameters* URouteParametersLibrary::Make(TArray<URouteParameter*> Parameters, FOptionalString Payload, FOptionalString ObjectId, UObject* Outer)
{
	auto Serializable = NewObject<URouteParameters>(Outer);
	Serializable->Parameters = Parameters;
	Serializable->Payload = Payload;
	Serializable->ObjectId = ObjectId;
	
	return Serializable;
}

void URouteParametersLibrary::Break(const URouteParameters* Serializable, TArray<URouteParameter*>& Parameters, FOptionalString& Payload, FOptionalString& ObjectId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Parameters = Serializable->Parameters;
		Payload = Serializable->Payload;
		ObjectId = Serializable->ObjectId;
	}
		
}

