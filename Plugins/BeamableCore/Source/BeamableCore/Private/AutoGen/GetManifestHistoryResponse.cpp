
#include "BeamableCore/Public/AutoGen/GetManifestHistoryResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetManifestHistoryResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetManifestHistoryResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UManifestSummary*>(TEXT("manifests"), Manifests, Serializer);
}

void UGetManifestHistoryResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UManifestSummary*>(TEXT("manifests"), Manifests, Serializer);		
}

void UGetManifestHistoryResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UManifestSummary*>(Bag->GetArrayField(TEXT("manifests")), Manifests, OuterOwner);
}



