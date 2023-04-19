
#include "BeamableCore/Public/AutoGen/ManifestSummary.h"
#include "Serialization/BeamJsonUtils.h"




void UManifestSummary::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("uid"), Uid);
	UBeamJsonUtils::SerializeUObject<UContentBasicManifestChecksum*>("manifest", Manifest, Serializer);
}

void UManifestSummary::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("uid"), Uid);
	UBeamJsonUtils::SerializeUObject<UContentBasicManifestChecksum*>("manifest", Manifest, Serializer);		
}

void UManifestSummary::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Uid = Bag->GetStringField(TEXT("uid"));
	UBeamJsonUtils::DeserializeUObject<UContentBasicManifestChecksum*>("manifest", Bag, Manifest, OuterOwner);
}



