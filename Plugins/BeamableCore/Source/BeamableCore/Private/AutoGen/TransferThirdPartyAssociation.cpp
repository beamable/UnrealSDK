
#include "BeamableCore/Public/AutoGen/TransferThirdPartyAssociation.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UTransferThirdPartyAssociation::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("fromAccountId"), FromAccountId, Serializer);
	UBeamJsonUtils::SerializeUObject<UThirdPartyAssociation*>("thirdParty", ThirdParty, Serializer);
}

void UTransferThirdPartyAssociation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("fromAccountId"), FromAccountId, Serializer);
	UBeamJsonUtils::SerializeUObject<UThirdPartyAssociation*>("thirdParty", ThirdParty, Serializer);		
}

void UTransferThirdPartyAssociation::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("fromAccountId")), FromAccountId);
	UBeamJsonUtils::DeserializeUObject<UThirdPartyAssociation*>("thirdParty", Bag, ThirdParty, OuterOwner);
}



