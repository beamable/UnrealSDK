
#include "BeamableCore/Public/AutoGen/TransferThirdPartyAssociation.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UTransferThirdPartyAssociation::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("fromAccountId"), FromAccountId);
	UBeamJsonUtils::SerializeUObject<UThirdPartyAssociation*>("thirdParty", ThirdParty, Serializer);
}

void UTransferThirdPartyAssociation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("fromAccountId"), FromAccountId);
	UBeamJsonUtils::SerializeUObject<UThirdPartyAssociation*>("thirdParty", ThirdParty, Serializer);		
}

void UTransferThirdPartyAssociation::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("fromAccountId")), FromAccountId);
	UBeamJsonUtils::DeserializeUObject<UThirdPartyAssociation*>("thirdParty", Bag, ThirdParty, OuterOwner);
}



