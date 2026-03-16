
#include "BeamableCore/Public/AutoGen/ManifestDiffSummary.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UManifestDiffSummary::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("manifestUid"), ManifestUid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("createdDate"), CreatedDate, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("affectedContentIds"), AffectedContentIds, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("publishedByName"), &PublishedByName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("publishedBy"), &PublishedBy, Serializer);
}

void UManifestDiffSummary::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("manifestUid"), ManifestUid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("createdDate"), CreatedDate, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("affectedContentIds"), AffectedContentIds, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("publishedByName"), &PublishedByName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("publishedBy"), &PublishedBy, Serializer);		
}

void UManifestDiffSummary::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("manifestUid"), Bag, ManifestUid);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("createdDate"), Bag, CreatedDate);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("affectedContentIds"), Bag, AffectedContentIds, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("publishedByName", Bag, PublishedByName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("publishedBy", Bag, PublishedBy, OuterOwner);
}



