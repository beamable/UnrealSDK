
#include "BeamableCore/Public/AutoGen/MultipliersGetResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UMultipliersGetResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UMultipliersGetResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UVipBonus*>(TEXT("multipliers"), Multipliers, Serializer);
}

void UMultipliersGetResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UVipBonus*>(TEXT("multipliers"), Multipliers, Serializer);		
}

void UMultipliersGetResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UVipBonus*>(Bag->GetArrayField(TEXT("multipliers")), Multipliers, OuterOwner);
}



