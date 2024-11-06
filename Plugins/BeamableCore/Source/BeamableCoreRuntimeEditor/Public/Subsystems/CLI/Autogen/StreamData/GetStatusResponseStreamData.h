
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ServiceStatusStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalArrayOfServiceDependencyReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceDependencyReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalArrayOfServiceStorageStatusStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceStorageStatusStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "GetStatusResponseStreamData.generated.h"


UCLASS()
class UGetStatusResponseStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	bool IsCurrent = {};
	UPROPERTY()
	TArray<UServiceStatusStreamData*> Services = {};
	UPROPERTY()
	UOptionalArrayOfServiceStorageStatusStreamData* StorageStatuses = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("isCurrent"), IsCurrent);
		UBeamJsonUtils::SerializeArray<UServiceStatusStreamData*>(TEXT("services"), Services, Serializer);
		UBeamJsonUtils::SerializeUObject<UOptionalArrayOfServiceStorageStatusStreamData*>("storageStatuses", StorageStatuses, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("isCurrent"), IsCurrent);
		UBeamJsonUtils::SerializeArray<UServiceStatusStreamData*>(TEXT("services"), Services, Serializer);
		UBeamJsonUtils::SerializeUObject<UOptionalArrayOfServiceStorageStatusStreamData*>("storageStatuses", StorageStatuses, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		IsCurrent = Bag->GetBoolField(TEXT("isCurrent"));
		UBeamJsonUtils::DeserializeArray<UServiceStatusStreamData*>(Bag->GetArrayField(TEXT("services")), Services, OuterOwner);
		UBeamJsonUtils::DeserializeUObject<UOptionalArrayOfServiceStorageStatusStreamData*>("storageStatuses", Bag, StorageStatuses, OuterOwner);	
	}
};


