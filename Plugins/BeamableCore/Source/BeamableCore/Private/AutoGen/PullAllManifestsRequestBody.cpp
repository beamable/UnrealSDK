
#include "BeamableCore/Public/AutoGen/PullAllManifestsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UPullAllManifestsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("sourceRealmPid"), &SourceRealmPid, Serializer);
}

void UPullAllManifestsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("sourceRealmPid"), &SourceRealmPid, Serializer);		
}

void UPullAllManifestsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("sourceRealmPid")), SourceRealmPid, OuterOwner);
}



