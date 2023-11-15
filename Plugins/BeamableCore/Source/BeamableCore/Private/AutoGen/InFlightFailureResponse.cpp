
#include "BeamableCore/Public/AutoGen/InFlightFailureResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UInFlightFailureResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UInFlightFailureResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UInFlightFailure*>(TEXT("failures"), Failures, Serializer);
}

void UInFlightFailureResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UInFlightFailure*>(TEXT("failures"), Failures, Serializer);		
}

void UInFlightFailureResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UInFlightFailure*>(Bag->GetArrayField(TEXT("failures")), Failures, OuterOwner);
}



