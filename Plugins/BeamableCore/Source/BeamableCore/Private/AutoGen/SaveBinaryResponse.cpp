
#include "BeamableCore/Public/AutoGen/SaveBinaryResponse.h"
#include "Serialization/BeamJsonUtils.h"



void USaveBinaryResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USaveBinaryResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UBinaryReference*>(TEXT("binary"), Binary, Serializer);
}

void USaveBinaryResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UBinaryReference*>(TEXT("binary"), Binary, Serializer);		
}

void USaveBinaryResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UBinaryReference*>(Bag->GetArrayField(TEXT("binary")), Binary, OuterOwner);
}



