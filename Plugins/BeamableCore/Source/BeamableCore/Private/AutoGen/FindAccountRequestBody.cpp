
#include "BeamableCore/Public/AutoGen/FindAccountRequestBody.h"





void UFindAccountRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("query"), Query);
}

void UFindAccountRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("query"), Query);		
}

void UFindAccountRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Query = Bag->GetStringField(TEXT("query"));
}



