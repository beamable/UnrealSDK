
#include "BeamableCore/Public/AutoGen/UnarchiveProjectRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UUnarchiveProjectRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("projectId"), &ProjectId, Serializer);
}

void UUnarchiveProjectRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("projectId"), &ProjectId, Serializer);		
}

void UUnarchiveProjectRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("projectId")), ProjectId, OuterOwner);
}



