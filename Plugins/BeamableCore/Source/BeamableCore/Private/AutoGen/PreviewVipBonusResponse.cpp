
#include "BeamableCore/Public/AutoGen/PreviewVipBonusResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UPreviewVipBonusResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UPreviewVipBonusResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UCurrencyPreview*>(TEXT("currencies"), Currencies, Serializer);
}

void UPreviewVipBonusResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UCurrencyPreview*>(TEXT("currencies"), Currencies, Serializer);		
}

void UPreviewVipBonusResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UCurrencyPreview*>(Bag->GetArrayField(TEXT("currencies")), Currencies, OuterOwner);
}



