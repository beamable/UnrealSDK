
#include "BeamableCore/Public/AutoGen/RouteVariables.h"
#include "Serialization/BeamJsonUtils.h"




void URouteVariables::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<URouteVariable*>(TEXT("variables"), Variables, Serializer);
}

void URouteVariables::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<URouteVariable*>(TEXT("variables"), Variables, Serializer);		
}

void URouteVariables::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<URouteVariable*>(Bag->GetArrayField(TEXT("variables")), Variables, OuterOwner);
}



