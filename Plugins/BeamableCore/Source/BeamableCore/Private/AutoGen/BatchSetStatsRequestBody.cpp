
#include "BeamableCore/Public/AutoGen/BatchSetStatsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UBatchSetStatsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UStatUpdateRequestBody*>(TEXT("updates"), Updates, Serializer);
}

void UBatchSetStatsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UStatUpdateRequestBody*>(TEXT("updates"), Updates, Serializer);		
}

void UBatchSetStatsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UStatUpdateRequestBody*>(Bag->GetArrayField(TEXT("updates")), Updates, OuterOwner);
}



