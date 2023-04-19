
#include "BeamableCore/Public/AutoGen/ArchiveOrUnarchiveManifestsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UArchiveOrUnarchiveManifestsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FBeamContentManifestId, FString>(TEXT("manifestIds"), ManifestIds, Serializer);
}

void UArchiveOrUnarchiveManifestsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FBeamContentManifestId, FString>(TEXT("manifestIds"), ManifestIds, Serializer);		
}

void UArchiveOrUnarchiveManifestsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<FBeamContentManifestId, FString>(Bag->GetArrayField(TEXT("manifestIds")), ManifestIds, OuterOwner);
}



