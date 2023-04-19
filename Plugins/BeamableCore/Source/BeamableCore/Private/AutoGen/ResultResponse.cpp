
#include "BeamableCore/Public/AutoGen/ResultResponse.h"




void UResultResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UResultResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), bResult);
}

void UResultResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), bResult);		
}

void UResultResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bResult = Bag->GetBoolField(TEXT("result"));
}



