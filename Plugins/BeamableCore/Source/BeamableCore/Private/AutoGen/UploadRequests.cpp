
#include "BeamableCore/Public/AutoGen/UploadRequests.h"
#include "Serialization/BeamJsonUtils.h"




void UUploadRequests::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UUploadRequestBody*>(TEXT("request"), Request, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("playerId"), &PlayerId, Serializer);
}

void UUploadRequests::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UUploadRequestBody*>(TEXT("request"), Request, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("playerId"), &PlayerId, Serializer);		
}

void UUploadRequests::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UUploadRequestBody*>(Bag->GetArrayField(TEXT("request")), Request, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("playerId", Bag, PlayerId, OuterOwner);
}



