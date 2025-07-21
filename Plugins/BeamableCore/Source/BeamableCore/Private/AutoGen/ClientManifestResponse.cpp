
#include "BeamableCore/Public/AutoGen/ClientManifestResponse.h"
#include "Serialization/BeamJsonUtils.h"




void UClientManifestResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UClientContentInfo*>(TEXT("items"), Items, Serializer);
}

void UClientManifestResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UClientContentInfo*>(TEXT("items"), Items, Serializer);		
}

void UClientManifestResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UClientContentInfo*>(Bag->GetArrayField(TEXT("items")), Items, OuterOwner);
}



