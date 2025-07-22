
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceRegistrationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ServiceRegistrationLibrary::BeamoV2ServiceRegistrationToJsonString(const UBeamoV2ServiceRegistration* Serializable, const bool Pretty)
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

UBeamoV2ServiceRegistration* UBeamoV2ServiceRegistrationLibrary::Make(FOptionalBool bTrafficFilterEnabled, FOptionalInt32 InstanceCount, FOptionalString ServiceName, FOptionalString Cid, FOptionalString Pid, FOptionalString BeamoName, FOptionalString RoutingKey, FOptionalInt64 StartedById, FOptionalArrayOfBeamoV2SupportedFederation Federation, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ServiceRegistration>(Outer);
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

void UBeamoV2ServiceRegistrationLibrary::Break(const UBeamoV2ServiceRegistration* Serializable, FOptionalBool& bTrafficFilterEnabled, FOptionalInt32& InstanceCount, FOptionalString& ServiceName, FOptionalString& Cid, FOptionalString& Pid, FOptionalString& BeamoName, FOptionalString& RoutingKey, FOptionalInt64& StartedById, FOptionalArrayOfBeamoV2SupportedFederation& Federation)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
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
		
}

