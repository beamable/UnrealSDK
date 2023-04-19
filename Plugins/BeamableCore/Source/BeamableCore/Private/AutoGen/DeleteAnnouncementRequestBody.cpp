
#include "BeamableCore/Public/AutoGen/DeleteAnnouncementRequestBody.h"





void UDeleteAnnouncementRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
}

void UDeleteAnnouncementRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);		
}

void UDeleteAnnouncementRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Symbol = Bag->GetStringField(TEXT("symbol"));
}



