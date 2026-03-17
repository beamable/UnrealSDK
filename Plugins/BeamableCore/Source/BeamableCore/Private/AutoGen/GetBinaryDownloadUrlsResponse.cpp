
#include "BeamableCore/Public/AutoGen/GetBinaryDownloadUrlsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetBinaryDownloadUrlsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetBinaryDownloadUrlsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UBinaryContentReference*>(TEXT("urls"), Urls, Serializer);
}

void UGetBinaryDownloadUrlsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UBinaryContentReference*>(TEXT("urls"), Urls, Serializer);		
}

void UGetBinaryDownloadUrlsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UBinaryContentReference*>(TEXT("urls"), Bag, Urls, OuterOwner);
}



