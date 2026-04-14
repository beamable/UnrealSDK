
#include "BeamableCore/Public/AutoGen/InFlightFailure.h"
#include "Serialization/BeamJsonUtils.h"




void UInFlightFailure::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceObjectId"), ServiceObjectId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeUObject<UInFlightMessage*>("inFlightMessage", InFlightMessage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastError"), LastError, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("timestamp"), &Timestamp, Serializer);
}

void UInFlightFailure::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceObjectId"), ServiceObjectId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeUObject<UInFlightMessage*>("inFlightMessage", InFlightMessage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastError"), LastError, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("timestamp"), &Timestamp, Serializer);		
}

void UInFlightFailure::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("serviceObjectId"), Bag, ServiceObjectId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("serviceName"), Bag, ServiceName);
	UBeamJsonUtils::DeserializeUObject<UInFlightMessage*>("inFlightMessage", Bag, InFlightMessage, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("lastError"), Bag, LastError);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("timestamp", Bag, Timestamp, OuterOwner);
}



