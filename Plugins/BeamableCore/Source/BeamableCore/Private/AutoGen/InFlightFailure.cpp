
#include "BeamableCore/Public/AutoGen/InFlightFailure.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UInFlightFailure::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("serviceObjectId"), ServiceObjectId);
	Serializer->WriteValue(TEXT("timestamp"), Timestamp);
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	UBeamJsonUtils::SerializeUObject<UInFlightMessage*>("inFlightMessage", InFlightMessage, Serializer);
	Serializer->WriteValue(TEXT("lastError"), LastError);
	Serializer->WriteValue(TEXT("id"), Id);
}

void UInFlightFailure::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("serviceObjectId"), ServiceObjectId);
	Serializer->WriteValue(TEXT("timestamp"), Timestamp);
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	UBeamJsonUtils::SerializeUObject<UInFlightMessage*>("inFlightMessage", InFlightMessage, Serializer);
	Serializer->WriteValue(TEXT("lastError"), LastError);
	Serializer->WriteValue(TEXT("id"), Id);		
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



