
#include "AutoGen/TransferRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UTransferRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("recipientPlayer"), RecipientPlayer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("transaction"), &Transaction, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, int64>, int64>(TEXT("currencies"), &Currencies, Serializer);
}

void UTransferRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("recipientPlayer"), RecipientPlayer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("transaction"), &Transaction, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, int64>, int64>(TEXT("currencies"), &Currencies, Serializer);		
}

void UTransferRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("recipientPlayer")), RecipientPlayer);
	UBeamJsonUtils::DeserializeOptional<FString>("transaction", Bag, Transaction, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, int64>, int64>("currencies", Bag, Currencies, OuterOwner);
}