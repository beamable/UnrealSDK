
#include "BeamableCore/Public/AutoGen/SendReq.h"
#include "Serialization/BeamJsonUtils.h"




void USendReq::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<USendMsg*>(TEXT("msgs"), Msgs, Serializer);
}

void USendReq::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<USendMsg*>(TEXT("msgs"), Msgs, Serializer);		
}

void USendReq::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<USendMsg*>(Bag->GetArrayField(TEXT("msgs")), Msgs, OuterOwner);
}



