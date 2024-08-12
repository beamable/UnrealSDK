
#include "BeamableCore/Public/AutoGen/MicroserviceRegistrationRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UMicroserviceRegistrationRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("trafficFilterEnabled"), &bTrafficFilterEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<USupportedFederation*>, USupportedFederation*>(TEXT("federation"), &Federation, Serializer);
}

void UMicroserviceRegistrationRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("trafficFilterEnabled"), &bTrafficFilterEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<USupportedFederation*>, USupportedFederation*>(TEXT("federation"), &Federation, Serializer);		
}

void UMicroserviceRegistrationRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ServiceName = Bag->GetStringField(TEXT("serviceName"));
	UBeamJsonUtils::DeserializeOptional<bool>("trafficFilterEnabled", Bag, bTrafficFilterEnabled, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("routingKey", Bag, RoutingKey, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<USupportedFederation*>, USupportedFederation*>("federation", Bag, Federation, OuterOwner);
}



