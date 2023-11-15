
#include "BeamableCore/Public/AutoGen/CommitImageRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UCommitImageRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UBeamoBasicReference*>("service", Service, Serializer);
}

void UCommitImageRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UBeamoBasicReference*>("service", Service, Serializer);		
}

void UCommitImageRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UBeamoBasicReference*>("service", Bag, Service, OuterOwner);
}



