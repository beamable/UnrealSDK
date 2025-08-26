
#include "BeamableCore/Public/AutoGen/RealmsBasicServicePlan.h"
#include "Serialization/BeamJsonUtils.h"




void URealmsBasicServicePlan::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeUObject<URealmsBasicDataDomain*>("dataDomain", DataDomain, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("minCustomerStatusSaved"), &MinCustomerStatusSaved, Serializer);
	UBeamJsonUtils::SerializeOptional<URealmsBasicServiceLimits*>(TEXT("limits"), &Limits, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);
}

void URealmsBasicServicePlan::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeUObject<URealmsBasicDataDomain*>("dataDomain", DataDomain, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("minCustomerStatusSaved"), &MinCustomerStatusSaved, Serializer);
	UBeamJsonUtils::SerializeOptional<URealmsBasicServiceLimits*>(TEXT("limits"), &Limits, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);		
}

void URealmsBasicServicePlan::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeUObject<URealmsBasicDataDomain*>("dataDomain", Bag, DataDomain, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("minCustomerStatusSaved", Bag, MinCustomerStatusSaved, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<URealmsBasicServiceLimits*>("limits", Bag, Limits, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("created", Bag, Created, OuterOwner);
}



