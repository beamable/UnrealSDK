
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"




void UMailSuccessResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UMailSuccessResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), bResult);
}

void UMailSuccessResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), bResult);		
}

void UMailSuccessResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bResult = Bag->GetBoolField(TEXT("result"));
}



