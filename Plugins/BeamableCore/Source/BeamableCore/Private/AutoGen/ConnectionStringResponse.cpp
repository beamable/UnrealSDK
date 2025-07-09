
#include "BeamableCore/Public/AutoGen/ConnectionStringResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UConnectionStringResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UConnectionStringResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("connectionString"), &ConnectionString, Serializer);
}

void UConnectionStringResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("connectionString"), &ConnectionString, Serializer);		
}

void UConnectionStringResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("connectionString", Bag, ConnectionString, OuterOwner);
}



