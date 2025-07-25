
#include "BeamableCore/Public/AutoGen/MicroserviceRegistrationsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


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

UMicroserviceRegistrations* UMicroserviceRegistrationsLibrary::Make(FString ServiceName, FString Cid, FString Pid, int32 InstanceCount, FOptionalBool bTrafficFilterEnabled, FOptionalString RoutingKey, FOptionalInt64 StartedById, FOptionalString BeamoName, FOptionalArrayOfSupportedFederation Federation, UObject* Outer)
{
	auto Serializable = NewObject<UMicroserviceRegistrations>(Outer);
	Serializable->ServiceName = ServiceName;
	Serializable->Cid = Cid;
	Serializable->Pid = Pid;
	Serializable->InstanceCount = InstanceCount;
	Serializable->bTrafficFilterEnabled = bTrafficFilterEnabled;
	Serializable->RoutingKey = RoutingKey;
	Serializable->StartedById = StartedById;
	Serializable->BeamoName = BeamoName;
	Serializable->Federation = Federation;
	
	return Serializable;
}

void UMicroserviceRegistrationsLibrary::Break(const UMicroserviceRegistrations* Serializable, FString& ServiceName, FString& Cid, FString& Pid, int32& InstanceCount, FOptionalBool& bTrafficFilterEnabled, FOptionalString& RoutingKey, FOptionalInt64& StartedById, FOptionalString& BeamoName, FOptionalArrayOfSupportedFederation& Federation)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ServiceName = Serializable->ServiceName;
		Cid = Serializable->Cid;
		Pid = Serializable->Pid;
		InstanceCount = Serializable->InstanceCount;
		bTrafficFilterEnabled = Serializable->bTrafficFilterEnabled;
		RoutingKey = Serializable->RoutingKey;
		StartedById = Serializable->StartedById;
		BeamoName = Serializable->BeamoName;
		Federation = Serializable->Federation;
	}
		
}

