
#include "AutoGen/RenameProjectRequestBody.h"



void URenameProjectRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("projectId"), ProjectId);
	Serializer->WriteValue(TEXT("newName"), NewName);
}

void URenameProjectRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("projectId"), ProjectId);
	Serializer->WriteValue(TEXT("newName"), NewName);		
}

void URenameProjectRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ProjectId = Bag->GetStringField(TEXT("projectId"));
	NewName = Bag->GetStringField(TEXT("newName"));
}