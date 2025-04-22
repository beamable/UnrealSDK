
#include "BeamableCore/Public/AutoGen/MailSearchClause.h"
#include "Serialization/BeamJsonUtils.h"




void UMailSearchClause::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("onlyCount"), bOnlyCount, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("forSender"), &ForSender, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("start"), &Start, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("categories"), &Categories, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("states"), &States, Serializer);
}

void UMailSearchClause::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("onlyCount"), bOnlyCount, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("forSender"), &ForSender, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("start"), &Start, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("categories"), &Categories, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("states"), &States, Serializer);		
}

void UMailSearchClause::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("onlyCount")), bOnlyCount);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
	UBeamJsonUtils::DeserializeOptional<int64>("forSender", Bag, ForSender, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("start", Bag, Start, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("limit", Bag, Limit, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("categories", Bag, Categories, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("states", Bag, States, OuterOwner);
}



