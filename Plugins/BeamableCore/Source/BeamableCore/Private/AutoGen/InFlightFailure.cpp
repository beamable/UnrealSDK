
#include "BeamableCore/Public/AutoGen/InFlightFailure.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UInFlightFailure::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceObjectId"), ServiceObjectId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("timestamp"), Timestamp, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeUObject<UInFlightMessage*>("inFlightMessage", InFlightMessage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastError"), LastError, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
}

void UInFlightFailure::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceObjectId"), ServiceObjectId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("timestamp"), Timestamp, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeUObject<UInFlightMessage*>("inFlightMessage", InFlightMessage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastError"), LastError, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);		
}

void UInFlightFailure::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("serviceObjectId")), ServiceObjectId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("timestamp")), Timestamp);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("serviceName")), ServiceName);
	UBeamJsonUtils::DeserializeUObject<UInFlightMessage*>("inFlightMessage", Bag, InFlightMessage, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("lastError")), LastError);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
}



