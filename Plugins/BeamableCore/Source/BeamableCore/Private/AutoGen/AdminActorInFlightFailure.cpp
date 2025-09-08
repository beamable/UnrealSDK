
#include "BeamableCore/Public/AutoGen/AdminActorInFlightFailure.h"
#include "Serialization/BeamJsonUtils.h"




void UAdminActorInFlightFailure::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("failureId"), FailureId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceObjectId"), ServiceObjectId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeUObject<UAdminActorInFlightMessage*>("inFlightMessage", InFlightMessage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastError"), LastError, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("timestamp"), &Timestamp, Serializer);
}

void UAdminActorInFlightFailure::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("failureId"), FailureId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceObjectId"), ServiceObjectId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeUObject<UAdminActorInFlightMessage*>("inFlightMessage", InFlightMessage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastError"), LastError, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("timestamp"), &Timestamp, Serializer);		
}

void UAdminActorInFlightFailure::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("failureId"), Bag, FailureId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("serviceObjectId"), Bag, ServiceObjectId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("serviceName"), Bag, ServiceName);
	UBeamJsonUtils::DeserializeUObject<UAdminActorInFlightMessage*>("inFlightMessage", Bag, InFlightMessage, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("lastError"), Bag, LastError);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("timestamp", Bag, Timestamp, OuterOwner);
}



