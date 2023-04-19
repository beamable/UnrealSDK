
#include "BeamableCore/Public/AutoGen/RankEntryStat.h"





void URankEntryStat::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("value"), Value);
}

void URankEntryStat::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("value"), Value);		
}

void URankEntryStat::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	Value = Bag->GetStringField(TEXT("value"));
}



