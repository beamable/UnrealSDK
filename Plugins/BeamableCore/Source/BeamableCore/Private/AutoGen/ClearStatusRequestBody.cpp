
#include "BeamableCore/Public/AutoGen/ClearStatusRequestBody.h"





void UClearStatusRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("store"), Store);
}

void UClearStatusRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("store"), Store);		
}

void UClearStatusRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Store = Bag->GetStringField(TEXT("store"));
}



