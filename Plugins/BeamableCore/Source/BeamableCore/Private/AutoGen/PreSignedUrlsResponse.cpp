
#include "BeamableCore/Public/AutoGen/PreSignedUrlsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UPreSignedUrlsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UPreSignedUrlsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UBeamoBasicURLResponse*>(TEXT("response"), Response, Serializer);
}

void UPreSignedUrlsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UBeamoBasicURLResponse*>(TEXT("response"), Response, Serializer);		
}

void UPreSignedUrlsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UBeamoBasicURLResponse*>(Bag->GetArrayField(TEXT("response")), Response, OuterOwner);
}



