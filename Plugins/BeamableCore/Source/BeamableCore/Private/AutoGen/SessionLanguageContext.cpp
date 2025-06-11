
#include "BeamableCore/Public/AutoGen/SessionLanguageContext.h"





void USessionLanguageContext::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("code"), Code, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("ctx"), Ctx, Serializer);
}

void USessionLanguageContext::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("code"), Code, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("ctx"), Ctx, Serializer);		
}

void USessionLanguageContext::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("code")), Code);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("ctx")), Ctx);
}



