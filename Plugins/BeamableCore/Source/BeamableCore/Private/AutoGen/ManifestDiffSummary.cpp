
#include "BeamableCore/Public/AutoGen/ManifestDiffSummary.h"

#include "Misc/DefaultValueHelper.h"



void UManifestDiffSummary::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("manifestUid"), ManifestUid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("diffUrl"), DiffUrl, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("createdDate"), CreatedDate, Serializer);
}

void UManifestDiffSummary::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("manifestUid"), ManifestUid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("diffUrl"), DiffUrl, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("createdDate"), CreatedDate, Serializer);		
}

void UManifestDiffSummary::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("manifestUid")), ManifestUid);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("diffUrl")), DiffUrl);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("createdDate")), CreatedDate);
}



