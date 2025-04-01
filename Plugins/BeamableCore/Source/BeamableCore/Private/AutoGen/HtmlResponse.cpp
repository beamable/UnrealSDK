
#include "BeamableCore/Public/AutoGen/HtmlResponse.h"





void UHtmlResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("html"), Html);
}

void UHtmlResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("html"), Html);		
}

void UHtmlResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Html = Bag->GetStringField(TEXT("html"));
}



