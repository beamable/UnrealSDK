
#include "BeamableCore/Public/AutoGen/ServiceTemplate.h"





void UServiceTemplate::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
}

void UServiceTemplate::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);		
}

void UServiceTemplate::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Id = Bag->GetStringField(TEXT("id"));
}



