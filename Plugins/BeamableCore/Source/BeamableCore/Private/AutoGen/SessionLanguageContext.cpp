
#include "BeamableCore/Public/AutoGen/SessionLanguageContext.h"





void USessionLanguageContext::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("code"), Code);
	Serializer->WriteValue(TEXT("ctx"), Ctx);
}

void USessionLanguageContext::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("code"), Code);
	Serializer->WriteValue(TEXT("ctx"), Ctx);		
}

void USessionLanguageContext::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("code")), Code);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("ctx")), Ctx);
}



