
#include "BeamableCore/Public/AutoGen/BatchDeleteInFlightRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UBatchDeleteInFlightRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("inFlightFailureIds"), InFlightFailureIds, Serializer);
}

void UBatchDeleteInFlightRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("inFlightFailureIds"), InFlightFailureIds, Serializer);		
}

void UBatchDeleteInFlightRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("inFlightFailureIds")), InFlightFailureIds, OuterOwner);
}



