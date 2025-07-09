
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("hasMore")), bHasMore);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("manifestId")), ManifestId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("totalCount")), TotalCount);
	UBeamJsonUtils::DeserializeArray<UManifestDiffSummary*>(Bag->GetArrayField(TEXT("diffs")), Diffs, OuterOwner);
}



