
#include "AutoGen/MailSearchClause.h"
#include "Serialization/BeamJsonUtils.h"


void UMailSearchClause ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("forSender"), &ForSender, Serializer);
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("onlyCount"), bOnlyCount);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("categories"), &Categories, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("start"), &Start, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("states"), &States, Serializer);
}

void UMailSearchClause::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("forSender"), &ForSender, Serializer);
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("onlyCount"), bOnlyCount);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("categories"), &Categories, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("start"), &Start, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("states"), &States, Serializer);		
}

void UMailSearchClause ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int64>("forSender", Bag, ForSender, OuterOwner);
	Name = Bag->GetStringField(TEXT("name"));
	bOnlyCount = Bag->GetBoolField(TEXT("onlyCount"));
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("categories", Bag, Categories, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("start", Bag, Start, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("limit", Bag, Limit, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("states", Bag, States, OuterOwner);
}