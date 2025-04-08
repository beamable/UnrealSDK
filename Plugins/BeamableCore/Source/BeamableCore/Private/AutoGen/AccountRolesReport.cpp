
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
	Serializer->WriteValue(TEXT("accountId"), AccountId);
	Serializer->WriteValue(TEXT("email"), Email);
	UBeamJsonUtils::SerializeArray<URealmRolesReport*>(TEXT("realms"), Realms, Serializer);
}

void UAccountRolesReport::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("accountId"), AccountId);
	Serializer->WriteValue(TEXT("email"), Email);
	UBeamJsonUtils::SerializeArray<URealmRolesReport*>(TEXT("realms"), Realms, Serializer);		
}

void UAccountRolesReport::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("accountId")), AccountId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("email")), Email);
	UBeamJsonUtils::DeserializeArray<URealmRolesReport*>(Bag->GetArrayField(TEXT("realms")), Realms, OuterOwner);
}



