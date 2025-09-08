
#include "BeamableCore/Public/AutoGen/RealmsBasicInFlightFailure.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void URealmsBasicInFlightFailure::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceObjectId"), ServiceObjectId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("timestamp"), Timestamp, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeUObject<URealmsBasicInFlightMessage*>("inFlightMessage", InFlightMessage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastError"), LastError, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
}

void URealmsBasicInFlightFailure::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceObjectId"), ServiceObjectId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("timestamp"), Timestamp, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeUObject<URealmsBasicInFlightMessage*>("inFlightMessage", InFlightMessage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastError"), LastError, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);		
}

void URealmsBasicInFlightFailure::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("serviceObjectId"), Bag, ServiceObjectId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("timestamp"), Bag, Timestamp);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("serviceName"), Bag, ServiceName);
	UBeamJsonUtils::DeserializeUObject<URealmsBasicInFlightMessage*>("inFlightMessage", Bag, InFlightMessage, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("lastError"), Bag, LastError);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
}



