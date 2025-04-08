
#include "BeamableCore/Public/AutoGen/GetTemplateRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UGetTemplateRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("templateName"), TemplateName);
	Serializer->WriteValue(TEXT("gamerTag"), GamerTag);
}

void UGetTemplateRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("templateName"), TemplateName);
	Serializer->WriteValue(TEXT("gamerTag"), GamerTag);		
}

void UGetTemplateRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("templateName")), TemplateName);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("gamerTag")), GamerTag);
}



