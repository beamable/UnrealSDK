
#include "BeamableCore/Public/AutoGen/ClientManifestResponse.h"
#include "Serialization/BeamJsonUtils.h"




void UClientManifestResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UClientContentInfo*>(TEXT("items"), Items, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdAt"), &CreatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("latestUpdate"), &LatestUpdate, Serializer);
}

void UClientManifestResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UClientContentInfo*>(TEXT("items"), Items, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdAt"), &CreatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("latestUpdate"), &LatestUpdate, Serializer);		
}

void UClientManifestResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UClientContentInfo*>(Bag->GetArrayField(TEXT("items")), Items, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("createdAt", Bag, CreatedAt, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("latestUpdate", Bag, LatestUpdate, OuterOwner);
}



