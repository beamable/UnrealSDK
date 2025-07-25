
#include "BeamableCore/Public/AutoGen/GetMailDetailsRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UGetMailDetailsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("mid"), Mid, Serializer);
}

void UGetMailDetailsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("mid"), Mid, Serializer);		
}

void UGetMailDetailsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("mid"), Bag, Mid);
}



