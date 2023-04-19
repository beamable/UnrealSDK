
#include "BeamableCore/Public/AutoGen/GetMailDetailsRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UGetMailDetailsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("mid"), Mid);
}

void UGetMailDetailsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("mid"), Mid);		
}

void UGetMailDetailsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("mid")), Mid);
}



