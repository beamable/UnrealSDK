
#include "BeamableCore/Public/AutoGen/GetManifestHistoryRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetManifestHistoryRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamContentManifestId, FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
}

void UGetManifestHistoryRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamContentManifestId, FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);		
}

void UGetManifestHistoryRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FBeamContentManifestId, FString>("id", Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("limit", Bag, Limit, OuterOwner);
}



