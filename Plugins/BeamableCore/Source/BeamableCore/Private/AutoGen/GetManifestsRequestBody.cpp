
#include "BeamableCore/Public/AutoGen/GetManifestsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetManifestsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("offset"), &Offset, Serializer);
}

void UGetManifestsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("offset"), &Offset, Serializer);		
}

void UGetManifestsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("archived", Bag, bArchived, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("limit", Bag, Limit, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("offset", Bag, Offset, OuterOwner);
}



