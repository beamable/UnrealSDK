
#include "BeamableCore/Public/AutoGen/ContentBasicGetManifestRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UContentBasicGetManifestRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamContentManifestId, FString>(TEXT("id"), &Id, Serializer);
}

void UContentBasicGetManifestRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamContentManifestId, FString>(TEXT("id"), &Id, Serializer);		
}

void UContentBasicGetManifestRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FBeamContentManifestId, FString>("id", Bag, Id, OuterOwner);
}



