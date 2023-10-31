
#include "BeamableCore/Public/AutoGen/CloudsavingBasicURLResponse.h"





void UCloudsavingBasicURLResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("url"), Url);
	Serializer->WriteValue(TEXT("objectKey"), ObjectKey);
}

void UCloudsavingBasicURLResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("url"), Url);
	Serializer->WriteValue(TEXT("objectKey"), ObjectKey);		
}

void UCloudsavingBasicURLResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Url = Bag->GetStringField(TEXT("url"));
	ObjectKey = Bag->GetStringField(TEXT("objectKey"));
}



