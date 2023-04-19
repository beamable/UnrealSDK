
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
	TemplateName = Bag->GetStringField(TEXT("templateName"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("gamerTag")), GamerTag);
}



