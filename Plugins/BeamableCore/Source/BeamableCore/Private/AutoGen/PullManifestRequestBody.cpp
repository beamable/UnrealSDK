
#include "BeamableCore/Public/AutoGen/PullManifestRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UPullManifestRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("sourceRealmPid"), &SourceRealmPid, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamContentManifestId, FString>(TEXT("id"), &Id, Serializer);
}

void UPullManifestRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("sourceRealmPid"), &SourceRealmPid, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamContentManifestId, FString>(TEXT("id"), &Id, Serializer);		
}

void UPullManifestRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("sourceRealmPid")), SourceRealmPid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamContentManifestId, FString>("id", Bag, Id, OuterOwner);
}



