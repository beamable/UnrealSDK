
#include "BeamableCore/Public/AutoGen/FailedInFlightFilterRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UFailedInFlightFilterRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceObjectId"), &ServiceObjectId, Serializer);
}

void UFailedInFlightFilterRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceObjectId"), &ServiceObjectId, Serializer);		
}

void UFailedInFlightFilterRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("serviceName")), ServiceName);
	UBeamJsonUtils::DeserializeOptional<FString>("serviceObjectId", Bag, ServiceObjectId, OuterOwner);
}



