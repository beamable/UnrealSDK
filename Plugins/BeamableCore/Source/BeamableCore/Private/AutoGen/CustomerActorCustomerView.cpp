
#include "BeamableCore/Public/AutoGen/CustomerActorCustomerView.h"
#include "Serialization/BeamJsonUtils.h"



void UCustomerActorCustomerView::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UCustomerActorCustomerView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("customerId"), CustomerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URealmView*>, URealmView*>(TEXT("realms"), &Realms, Serializer);
}

void UCustomerActorCustomerView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("customerId"), CustomerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URealmView*>, URealmView*>(TEXT("realms"), &Realms, Serializer);		
}

void UCustomerActorCustomerView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("customerId"), Bag, CustomerId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeOptional<FString>("alias", Bag, Alias, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<URealmView*>, URealmView*>("realms", Bag, Realms, OuterOwner);
}



