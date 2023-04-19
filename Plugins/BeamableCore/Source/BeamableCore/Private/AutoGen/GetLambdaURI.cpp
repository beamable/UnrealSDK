
#include "BeamableCore/Public/AutoGen/GetLambdaURI.h"




void UGetLambdaURI::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetLambdaURI::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("uri"), Uri);
}

void UGetLambdaURI::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("uri"), Uri);		
}

void UGetLambdaURI::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Uri = Bag->GetStringField(TEXT("uri"));
}



