
#include "BeamableCore/Public/AutoGen/RouteParameterLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URouteParameterLibrary::RouteParameterToJsonString(const URouteParameter* Serializable, const bool Pretty)
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

URouteParameter* URouteParameterLibrary::Make(FString Name, FString Body, FString TypeName, FOptionalVariableReference VariableRef, UObject* Outer)
{
	auto Serializable = NewObject<URouteParameter>(Outer);
	Serializable->Name = Name;
	Serializable->Body = Body;
	Serializable->TypeName = TypeName;
	Serializable->VariableRef = VariableRef;
	
	return Serializable;
}

void URouteParameterLibrary::Break(const URouteParameter* Serializable, FString& Name, FString& Body, FString& TypeName, FOptionalVariableReference& VariableRef)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Body = Serializable->Body;
		TypeName = Serializable->TypeName;
		VariableRef = Serializable->VariableRef;
	}
		
}

