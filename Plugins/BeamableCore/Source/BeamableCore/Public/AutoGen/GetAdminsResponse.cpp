
#include "AutoGen/GetAdminsResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UGetAdminsResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UAccountPortalView*>(TEXT("accounts"), Accounts, Serializer);
}

void UGetAdminsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UAccountPortalView*>(TEXT("accounts"), Accounts, Serializer);		
}

void UGetAdminsResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UAccountPortalView*>(Bag->GetArrayField(TEXT("accounts")), Accounts, OuterOwner);
}