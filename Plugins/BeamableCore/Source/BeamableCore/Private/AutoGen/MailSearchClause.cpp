
#include "BeamableCore/Public/AutoGen/MailSearchClause.h"
#include "Serialization/BeamJsonUtils.h"




void UMailSearchClause::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("onlyCount"), bOnlyCount);
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("forSender"), &ForSender, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("start"), &Start, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("categories"), &Categories, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("states"), &States, Serializer);
}

void UMailSearchClause::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("onlyCount"), bOnlyCount);
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("forSender"), &ForSender, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("start"), &Start, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("categories"), &Categories, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("states"), &States, Serializer);		
}

void UMailSearchClause::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bOnlyCount = Bag->GetBoolField(TEXT("onlyCount"));
	Name = Bag->GetStringField(TEXT("name"));
	UBeamJsonUtils::DeserializeOptional<int64>("forSender", Bag, ForSender, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("start", Bag, Start, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("limit", Bag, Limit, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("categories", Bag, Categories, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("states", Bag, States, OuterOwner);
}



