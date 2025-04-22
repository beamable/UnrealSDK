
#include "BeamableCore/Public/AutoGen/RenameProjectRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void URenameProjectRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("projectId"), &ProjectId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("newName"), NewName, Serializer);
}

void URenameProjectRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("projectId"), &ProjectId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("newName"), NewName, Serializer);		
}

void URenameProjectRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("projectId")), ProjectId, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("newName")), NewName);
}



