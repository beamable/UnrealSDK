
#include "BeamableCore/Public/AutoGen/TransferRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UTransferRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("recipientPlayer"), &RecipientPlayer, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("transaction"), &Transaction, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, int64>, int64>(TEXT("currencies"), &Currencies, Serializer);
}

void UTransferRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("recipientPlayer"), &RecipientPlayer, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("transaction"), &Transaction, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, int64>, int64>(TEXT("currencies"), &Currencies, Serializer);		
}

void UTransferRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<int64>(Bag->TryGetField(TEXT("recipientPlayer")), RecipientPlayer, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("transaction", Bag, Transaction, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, int64>, int64>("currencies", Bag, Currencies, OuterOwner);
}



