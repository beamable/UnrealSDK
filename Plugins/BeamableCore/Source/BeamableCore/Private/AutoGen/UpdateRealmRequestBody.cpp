
#include "BeamableCore/Public/AutoGen/UpdateRealmRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UUpdateRealmRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archiveStatus"), &bArchiveStatus, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hiddenStatus"), &bHiddenStatus, Serializer);
}

void UUpdateRealmRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archiveStatus"), &bArchiveStatus, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hiddenStatus"), &bHiddenStatus, Serializer);		
}

void UUpdateRealmRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("archiveStatus", Bag, bArchiveStatus, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("hiddenStatus", Bag, bHiddenStatus, OuterOwner);
}



