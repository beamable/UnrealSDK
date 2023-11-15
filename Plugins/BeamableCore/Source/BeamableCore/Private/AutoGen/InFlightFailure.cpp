
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
	ServiceObjectId = Bag->GetStringField(TEXT("serviceObjectId"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("timestamp")), Timestamp);
	ServiceName = Bag->GetStringField(TEXT("serviceName"));
	UBeamJsonUtils::DeserializeUObject<UInFlightMessage*>("inFlightMessage", Bag, InFlightMessage, OuterOwner);
	LastError = Bag->GetStringField(TEXT("lastError"));
	Id = Bag->GetStringField(TEXT("id"));
}



