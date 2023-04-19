
#include "BeamableCore/Public/AutoGen/AccountSearchResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UAccountSearchResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAccountSearchResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UAccountsBasicAccount*>(TEXT("accounts"), Accounts, Serializer);
}

void UAccountSearchResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UAccountsBasicAccount*>(TEXT("accounts"), Accounts, Serializer);		
}

void UAccountSearchResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UAccountsBasicAccount*>(Bag->GetArrayField(TEXT("accounts")), Accounts, OuterOwner);
}



