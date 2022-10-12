
#include "AutoGen/URLSResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UURLSResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UURLResponse*>(TEXT("response"), Response, Serializer);
}

void UURLSResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UURLResponse*>(TEXT("response"), Response, Serializer);		
}

void UURLSResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UURLResponse*>(Bag->GetArrayField(TEXT("response")), Response, OuterOwner);
}