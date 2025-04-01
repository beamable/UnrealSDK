
#include "BeamableCore/Public/AutoGen/ActivationRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UActivationRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("token"), Token);
	Serializer->WriteValue(TEXT("cid"), Cid);
}

void UActivationRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("token"), Token);
	Serializer->WriteValue(TEXT("cid"), Cid);		
}

void UActivationRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Token = Bag->GetStringField(TEXT("token"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("cid")), Cid);
}



