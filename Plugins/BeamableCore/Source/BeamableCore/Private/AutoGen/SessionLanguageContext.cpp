
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
	Code = Bag->GetStringField(TEXT("code"));
	Ctx = Bag->GetStringField(TEXT("ctx"));
}



