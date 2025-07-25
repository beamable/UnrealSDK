
#include "BeamableCore/Public/AutoGen/ManifestSummary.h"
#include "Serialization/BeamJsonUtils.h"




void UManifestSummary::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("uid"), Uid, Serializer);
	UBeamJsonUtils::SerializeUObject<UContentBasicManifestChecksum*>("manifest", Manifest, Serializer);
}

void UManifestSummary::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("uid"), Uid, Serializer);
	UBeamJsonUtils::SerializeUObject<UContentBasicManifestChecksum*>("manifest", Manifest, Serializer);		
}

void UManifestSummary::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("uid"), Bag, Uid);
	UBeamJsonUtils::DeserializeUObject<UContentBasicManifestChecksum*>("manifest", Bag, Manifest, OuterOwner);
}



