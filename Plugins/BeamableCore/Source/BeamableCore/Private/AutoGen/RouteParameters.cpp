
#include "BeamableCore/Public/AutoGen/RouteParameters.h"
#include "Serialization/BeamJsonUtils.h"




void URouteParameters::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<URouteParameter*>(TEXT("parameters"), Parameters, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("payload"), &Payload, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("objectId"), &ObjectId, Serializer);
}

void URouteParameters::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<URouteParameter*>(TEXT("parameters"), Parameters, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("payload"), &Payload, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("objectId"), &ObjectId, Serializer);		
}

void URouteParameters::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<URouteParameter*>(Bag->GetArrayField(TEXT("parameters")), Parameters, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("payload", Bag, Payload, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("objectId", Bag, ObjectId, OuterOwner);
}



