
#include "BeamableCore/Public/AutoGen/CustomerActorPromoteRealmResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UCustomerActorPromoteRealmResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UCustomerActorPromoteRealmResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sourceRealmId"), SourceRealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UPromotionScope*>, UPromotionScope*>(TEXT("scopes"), &Scopes, Serializer);
}

void UCustomerActorPromoteRealmResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sourceRealmId"), SourceRealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UPromotionScope*>, UPromotionScope*>(TEXT("scopes"), &Scopes, Serializer);		
}

void UCustomerActorPromoteRealmResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("sourceRealmId"), Bag, SourceRealmId);
	UBeamJsonUtils::DeserializeOptional<TArray<UPromotionScope*>, UPromotionScope*>("scopes", Bag, Scopes, OuterOwner);
}



