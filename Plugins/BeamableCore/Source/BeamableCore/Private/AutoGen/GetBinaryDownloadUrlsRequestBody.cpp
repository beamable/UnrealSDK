
#include "BeamableCore/Public/AutoGen/GetBinaryDownloadUrlsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetBinaryDownloadUrlsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UGetContentRequestBody*>(TEXT("requests"), Requests, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expirationSeconds"), &ExpirationSeconds, Serializer);
}

void UGetBinaryDownloadUrlsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UGetContentRequestBody*>(TEXT("requests"), Requests, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expirationSeconds"), &ExpirationSeconds, Serializer);		
}

void UGetBinaryDownloadUrlsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UGetContentRequestBody*>(TEXT("requests"), Bag, Requests, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("expirationSeconds", Bag, ExpirationSeconds, OuterOwner);
}



