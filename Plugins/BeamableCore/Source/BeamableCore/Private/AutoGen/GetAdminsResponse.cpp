
#include "BeamableCore/Public/AutoGen/GetAdminsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetAdminsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetAdminsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UAccountPortalView*>(TEXT("accounts"), Accounts, Serializer);
}

void UGetAdminsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UAccountPortalView*>(TEXT("accounts"), Accounts, Serializer);		
}

void UGetAdminsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UAccountPortalView*>(Bag->GetArrayField(TEXT("accounts")), Accounts, OuterOwner);
}



