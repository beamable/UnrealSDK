
#include "BeamableCore/Public/AutoGen/ManifestChecksums.h"
#include "Serialization/BeamJsonUtils.h"



void UManifestChecksums::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UManifestChecksums::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UContentBasicManifestChecksum*>(TEXT("manifests"), Manifests, Serializer);
}

void UManifestChecksums::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UContentBasicManifestChecksum*>(TEXT("manifests"), Manifests, Serializer);		
}

void UManifestChecksums::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UContentBasicManifestChecksum*>(Bag->GetArrayField(TEXT("manifests")), Manifests, OuterOwner);
}



