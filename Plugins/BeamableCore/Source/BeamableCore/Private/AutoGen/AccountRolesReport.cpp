
#include "BeamableCore/Public/AutoGen/AccountRolesReport.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UAccountRolesReport::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAccountRolesReport::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("accountId"), AccountId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("email"), Email, Serializer);
	UBeamJsonUtils::SerializeArray<URealmRolesReport*>(TEXT("realms"), Realms, Serializer);
}

void UAccountRolesReport::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("accountId"), AccountId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("email"), Email, Serializer);
	UBeamJsonUtils::SerializeArray<URealmRolesReport*>(TEXT("realms"), Realms, Serializer);		
}

void UAccountRolesReport::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("accountId")), AccountId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("email")), Email);
	UBeamJsonUtils::DeserializeArray<URealmRolesReport*>(Bag->GetArrayField(TEXT("realms")), Realms, OuterOwner);
}



