
#include "BeamableCore/Public/AutoGen/ServiceRegistrationQueryLibrary.h"

#include "CoreMinimal.h"


FString UServiceRegistrationQueryLibrary::ServiceRegistrationQueryToJsonString(const UServiceRegistrationQuery* Serializable, const bool Pretty)
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

UServiceRegistrationQuery* UServiceRegistrationQueryLibrary::Make(FOptionalBool bLocalOnly, FOptionalString ServiceName, FOptionalString RoutingKey, FOptionalSupportedFederation Federation, UObject* Outer)
{
	auto Serializable = NewObject<UServiceRegistrationQuery>(Outer);
	Serializable->bLocalOnly = bLocalOnly;
	Serializable->ServiceName = ServiceName;
	Serializable->RoutingKey = RoutingKey;
	Serializable->Federation = Federation;
	
	return Serializable;
}

void UServiceRegistrationQueryLibrary::Break(const UServiceRegistrationQuery* Serializable, FOptionalBool& bLocalOnly, FOptionalString& ServiceName, FOptionalString& RoutingKey, FOptionalSupportedFederation& Federation)
{
	bLocalOnly = Serializable->bLocalOnly;
	ServiceName = Serializable->ServiceName;
	RoutingKey = Serializable->RoutingKey;
	Federation = Serializable->Federation;
		
}

