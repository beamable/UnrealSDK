
#include "BeamableCore/Public/AutoGen/RenameProjectRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void URenameProjectRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("projectId"), &ProjectId, Serializer);
	Serializer->WriteValue(TEXT("newName"), NewName);
}

void URenameProjectRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("projectId"), &ProjectId, Serializer);
	Serializer->WriteValue(TEXT("newName"), NewName);		
}

void URenameProjectRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("projectId")), ProjectId, OuterOwner);
	NewName = Bag->GetStringField(TEXT("newName"));
}



