
#include "BeamableCore/Public/AutoGen/RouteVariablesLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URouteVariablesLibrary::RouteVariablesToJsonString(const URouteVariables* Serializable, const bool Pretty)
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

URouteVariables* URouteVariablesLibrary::Make(TArray<URouteVariable*> Variables, UObject* Outer)
{
	auto Serializable = NewObject<URouteVariables>(Outer);
	Serializable->Variables = Variables;
	
	return Serializable;
}

void URouteVariablesLibrary::Break(const URouteVariables* Serializable, TArray<URouteVariable*>& Variables)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Variables = Serializable->Variables;
	}
		
}

