
#include "BeamableCore/Public/AutoGen/GetExactManifestRequestBody.h"





void UGetExactManifestRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("uid"), Uid);
}

void UGetExactManifestRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("uid"), Uid);		
}

void UGetExactManifestRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Uid = Bag->GetStringField(TEXT("uid"));
}



