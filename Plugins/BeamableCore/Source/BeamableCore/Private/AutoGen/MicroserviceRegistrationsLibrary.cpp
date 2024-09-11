
#include "BeamableCore/Public/AutoGen/MicroserviceRegistrationsLibrary.h"

#include "CoreMinimal.h"


FString UMicroserviceRegistrationsLibrary::MicroserviceRegistrationsToJsonString(const UMicroserviceRegistrations* Serializable, const bool Pretty)
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

UMicroserviceRegistrations* UMicroserviceRegistrationsLibrary::Make(FString ServiceName, FString Cid, FString Pid, int32 InstanceCount, FOptionalBool bTrafficFilterEnabled, FOptionalInt64 StartedByGamerTag, FOptionalString RoutingKey, FOptionalString BeamoName, FOptionalArrayOfSupportedFederation Federation, UObject* Outer)
{
	auto Serializable = NewObject<UMicroserviceRegistrations>(Outer);
	Serializable->ServiceName = ServiceName;
	Serializable->Cid = Cid;
	Serializable->Pid = Pid;
	Serializable->InstanceCount = InstanceCount;
	Serializable->bTrafficFilterEnabled = bTrafficFilterEnabled;
	Serializable->StartedByGamerTag = StartedByGamerTag;
	Serializable->RoutingKey = RoutingKey;
	Serializable->BeamoName = BeamoName;
	Serializable->Federation = Federation;
	
	return Serializable;
}

void UMicroserviceRegistrationsLibrary::Break(const UMicroserviceRegistrations* Serializable, FString& ServiceName, FString& Cid, FString& Pid, int32& InstanceCount, FOptionalBool& bTrafficFilterEnabled, FOptionalInt64& StartedByGamerTag, FOptionalString& RoutingKey, FOptionalString& BeamoName, FOptionalArrayOfSupportedFederation& Federation)
{
	ServiceName = Serializable->ServiceName;
	Cid = Serializable->Cid;
	Pid = Serializable->Pid;
	InstanceCount = Serializable->InstanceCount;
	bTrafficFilterEnabled = Serializable->bTrafficFilterEnabled;
	StartedByGamerTag = Serializable->StartedByGamerTag;
	RoutingKey = Serializable->RoutingKey;
	BeamoName = Serializable->BeamoName;
	Federation = Serializable->Federation;
		
}

