
#include "BeamableCore/Public/AutoGen/AdminGetPlayerStatusResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UAdminGetPlayerStatusResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAdminGetPlayerStatusResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UAdminPlayerStatus*>(TEXT("statuses"), Statuses, Serializer);
}

void UAdminGetPlayerStatusResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UAdminPlayerStatus*>(TEXT("statuses"), Statuses, Serializer);		
}

void UAdminGetPlayerStatusResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UAdminPlayerStatus*>(Bag->GetArrayField(TEXT("statuses")), Statuses, OuterOwner);
}



