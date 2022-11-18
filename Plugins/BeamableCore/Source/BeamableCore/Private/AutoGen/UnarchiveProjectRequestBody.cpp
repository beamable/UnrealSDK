
#include "AutoGen/UnarchiveProjectRequestBody.h"





void UUnarchiveProjectRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("projectId"), ProjectId);
}

void UUnarchiveProjectRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("projectId"), ProjectId);		
}

void UUnarchiveProjectRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ProjectId = Bag->GetStringField(TEXT("projectId"));
}