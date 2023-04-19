
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
	ContentId = Bag->GetStringField(TEXT("contentId"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("id")), Id);
}



