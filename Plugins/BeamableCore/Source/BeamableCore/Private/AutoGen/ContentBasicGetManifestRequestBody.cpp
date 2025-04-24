
#include "BeamableCore/Public/AutoGen/ContentBasicGetManifestRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UContentBasicGetManifestRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamContentManifestId, FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("uid"), &Uid, Serializer);
}

void UContentBasicGetManifestRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamContentManifestId, FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("uid"), &Uid, Serializer);		
}

void UContentBasicGetManifestRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FBeamContentManifestId, FString>("id", Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("uid", Bag, Uid, OuterOwner);
}



