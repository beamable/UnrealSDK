
#include "BeamableCore/Public/AutoGen/GetPlayerStatusResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetPlayerStatusResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetPlayerStatusResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UPlayerStatus*>(TEXT("statuses"), Statuses, Serializer);
}

void UGetPlayerStatusResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UPlayerStatus*>(TEXT("statuses"), Statuses, Serializer);		
}

void UGetPlayerStatusResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UPlayerStatus*>(Bag->GetArrayField(TEXT("statuses")), Statuses, OuterOwner);
}



