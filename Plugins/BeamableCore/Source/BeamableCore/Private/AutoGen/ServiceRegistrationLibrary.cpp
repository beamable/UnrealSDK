
#include "BeamableCore/Public/AutoGen/ServiceRegistrationLibrary.h"

#include "CoreMinimal.h"


FString UServiceRegistrationLibrary::ServiceRegistrationToJsonString(const UServiceRegistration* Serializable, const bool Pretty)
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

UServiceRegistration* UServiceRegistrationLibrary::Make(FOptionalBool bTrafficFilterEnabled, FOptionalInt32 InstanceCount, FOptionalString ServiceName, FOptionalString Cid, FOptionalString Pid, FOptionalString BeamoName, FOptionalString RoutingKey, FOptionalInt64 StartedById, FOptionalArrayOfSupportedFederation Federation, UObject* Outer)
{
	auto Serializable = NewObject<UServiceRegistration>(Outer);
	Serializable->bTrafficFilterEnabled = bTrafficFilterEnabled;
	Serializable->InstanceCount = InstanceCount;
	Serializable->ServiceName = ServiceName;
	Serializable->Cid = Cid;
	Serializable->Pid = Pid;
	Serializable->BeamoName = BeamoName;
	Serializable->RoutingKey = RoutingKey;
	Serializable->StartedById = StartedById;
	Serializable->Federation = Federation;
	
	return Serializable;
}

void UServiceRegistrationLibrary::Break(const UServiceRegistration* Serializable, FOptionalBool& bTrafficFilterEnabled, FOptionalInt32& InstanceCount, FOptionalString& ServiceName, FOptionalString& Cid, FOptionalString& Pid, FOptionalString& BeamoName, FOptionalString& RoutingKey, FOptionalInt64& StartedById, FOptionalArrayOfSupportedFederation& Federation)
{
	bTrafficFilterEnabled = Serializable->bTrafficFilterEnabled;
	InstanceCount = Serializable->InstanceCount;
	ServiceName = Serializable->ServiceName;
	Cid = Serializable->Cid;
	Pid = Serializable->Pid;
	BeamoName = Serializable->BeamoName;
	RoutingKey = Serializable->RoutingKey;
	StartedById = Serializable->StartedById;
	Federation = Serializable->Federation;
		
}

