
#include "BeamableCore/Public/AutoGen/GetManifestDiffsResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UGetManifestDiffsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetManifestDiffsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("hasMore"), bHasMore, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("manifestId"), ManifestId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("totalCount"), TotalCount, Serializer);
	UBeamJsonUtils::SerializeArray<UManifestDiffSummary*>(TEXT("diffs"), Diffs, Serializer);
}

void UGetManifestDiffsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("hasMore"), bHasMore, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("manifestId"), ManifestId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("totalCount"), TotalCount, Serializer);
	UBeamJsonUtils::SerializeArray<UManifestDiffSummary*>(TEXT("diffs"), Diffs, Serializer);		
}

void UGetManifestDiffsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("hasMore"), Bag, bHasMore);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("manifestId"), Bag, ManifestId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("totalCount"), Bag, TotalCount);
	UBeamJsonUtils::DeserializeArray<UManifestDiffSummary*>(TEXT("diffs"), Bag, Diffs, OuterOwner);
}



