
#include "BeamableCore/Public/AutoGen/GroupCreateResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGroupCreateResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGroupCreateResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UGroupMetaData*>("group", Group, Serializer);
}

void UGroupCreateResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UGroupMetaData*>("group", Group, Serializer);		
}

void UGroupCreateResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UGroupMetaData*>("group", Bag, Group, OuterOwner);
}



