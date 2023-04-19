
#include "BeamableCore/Public/AutoGen/UploadRequestsFromPortal.h"
#include "Serialization/BeamJsonUtils.h"




void UUploadRequestsFromPortal::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UUploadRequestFromPortal*>(TEXT("request"), Request, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("playerId"), &PlayerId, Serializer);
}

void UUploadRequestsFromPortal::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UUploadRequestFromPortal*>(TEXT("request"), Request, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("playerId"), &PlayerId, Serializer);		
}

void UUploadRequestsFromPortal::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UUploadRequestFromPortal*>(Bag->GetArrayField(TEXT("request")), Request, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("playerId", Bag, PlayerId, OuterOwner);
}



