
#include "AutoGen/PostManifestResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UPostManifestResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UPostManifestResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UManifestChecksum*>(TEXT("manifest"), &Manifest, Serializer);
}

void UPostManifestResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UManifestChecksum*>(TEXT("manifest"), &Manifest, Serializer);		
}

void UPostManifestResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<UManifestChecksum*>("manifest", Bag, Manifest, OuterOwner);
}