
#include "BeamableCore/Public/AutoGen/RealmView.h"
#include "Serialization/BeamJsonUtils.h"



void URealmView::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void URealmView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("displayName"), DisplayName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("realmId"), RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("sharded"), &bSharded, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("parent"), &Parent, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("secret"), &Secret, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("children"), &Children, Serializer);
}

void URealmView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("displayName"), DisplayName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("realmId"), RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("sharded"), &bSharded, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("parent"), &Parent, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("secret"), &Secret, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("children"), &Children, Serializer);		
}

void URealmView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("displayName"), Bag, DisplayName);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("realmId"), Bag, RealmId);
	UBeamJsonUtils::DeserializeOptional<bool>("archived", Bag, bArchived, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("sharded", Bag, bSharded, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("customerId", Bag, CustomerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("parent", Bag, Parent, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("secret", Bag, Secret, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("children", Bag, Children, OuterOwner);
}



