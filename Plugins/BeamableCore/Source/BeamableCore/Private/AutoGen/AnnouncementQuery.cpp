
#include "BeamableCore/Public/AutoGen/AnnouncementQuery.h"
#include "Serialization/BeamJsonUtils.h"




void UAnnouncementQuery::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("include_deleted"), &bIncludeDeleted, Serializer);
}

void UAnnouncementQuery::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("include_deleted"), &bIncludeDeleted, Serializer);		
}

void UAnnouncementQuery::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("include_deleted", Bag, bIncludeDeleted, OuterOwner);
}



