
#include "BeamableCore/Public/AutoGen/GetTemplateRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UGetTemplateRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("templateName"), TemplateName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);
}

void UGetTemplateRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("templateName"), TemplateName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);		
}

void UGetTemplateRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("templateName"), Bag, TemplateName);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("gamerTag"), Bag, GamerTag);
}



