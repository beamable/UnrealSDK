
#include "BeamableCore/Public/AutoGen/BeamoV2ConnectionStringResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UBeamoV2ConnectionStringResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoV2ConnectionStringResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("connectionString"), &ConnectionString, Serializer);
}

void UBeamoV2ConnectionStringResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("connectionString"), &ConnectionString, Serializer);		
}

void UBeamoV2ConnectionStringResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("connectionString", Bag, ConnectionString, OuterOwner);
}



