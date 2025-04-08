
#include "BeamableCore/Public/AutoGen/ItemDeleteRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UItemDeleteRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("contentId"), ContentId);
	Serializer->WriteValue(TEXT("id"), Id);
}

void UItemDeleteRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("contentId"), ContentId);
	Serializer->WriteValue(TEXT("id"), Id);		
}

void UItemDeleteRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("contentId")), ContentId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
}



