
#include "BeamableCore/Public/AutoGen/AvailableRolesResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UAvailableRolesResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAvailableRolesResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("roles"), Roles, Serializer);
}

void UAvailableRolesResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("roles"), Roles, Serializer);		
}

void UAvailableRolesResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("roles")), Roles, OuterOwner);
}



