
#include "AutoGen/ServicePlan.h"
#include "Serialization/BeamJsonUtils.h"


void UServicePlan ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("minCustomerStatusSaved"), &MinCustomerStatusSaved, Serializer);
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeUObject<UDataDomain*>("dataDomain", DataDomain, Serializer);
	UBeamJsonUtils::SerializeOptional<UServiceLimits*>(TEXT("limits"), &Limits, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);
}

void UServicePlan::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("minCustomerStatusSaved"), &MinCustomerStatusSaved, Serializer);
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeUObject<UDataDomain*>("dataDomain", DataDomain, Serializer);
	UBeamJsonUtils::SerializeOptional<UServiceLimits*>(TEXT("limits"), &Limits, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);		
}

void UServicePlan ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("minCustomerStatusSaved", Bag, MinCustomerStatusSaved, OuterOwner);
	Name = Bag->GetStringField(TEXT("name"));
	UBeamJsonUtils::DeserializeUObject<UDataDomain*>("dataDomain", Bag, DataDomain, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UServiceLimits*>("limits", Bag, Limits, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("created", Bag, Created, OuterOwner);
}