
#include "BeamableCore/Public/AutoGen/ContextInfo.h"





void UContextInfo::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("platform"), Platform);
	Serializer->WriteValue(TEXT("device"), Device);
}

void UContextInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("platform"), Platform);
	Serializer->WriteValue(TEXT("device"), Device);		
}

void UContextInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Platform = Bag->GetStringField(TEXT("platform"));
	Device = Bag->GetStringField(TEXT("device"));
}



