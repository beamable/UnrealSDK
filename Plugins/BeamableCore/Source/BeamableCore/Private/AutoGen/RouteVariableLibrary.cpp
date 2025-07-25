
#include "BeamableCore/Public/AutoGen/RouteVariableLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URouteVariableLibrary::RouteVariableToJsonString(const URouteVariable* Serializable, const bool Pretty)
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

URouteVariable* URouteVariableLibrary::Make(FString Name, FString TypeName, UObject* Outer)
{
	auto Serializable = NewObject<URouteVariable>(Outer);
	Serializable->Name = Name;
	Serializable->TypeName = TypeName;
	
	return Serializable;
}

void URouteVariableLibrary::Break(const URouteVariable* Serializable, FString& Name, FString& TypeName)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		TypeName = Serializable->TypeName;
	}
		
}

