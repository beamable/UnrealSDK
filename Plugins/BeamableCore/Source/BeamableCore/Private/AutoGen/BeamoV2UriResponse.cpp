
#include "BeamableCore/Public/AutoGen/BeamoV2UriResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UBeamoV2UriResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoV2UriResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("uri"), &Uri, Serializer);
}

void UBeamoV2UriResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("uri"), &Uri, Serializer);		
}

void UBeamoV2UriResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("uri", Bag, Uri, OuterOwner);
}



