
#include "BeamableCore/Public/AutoGen/RealmsBasicPromoteRealmResponse.h"
#include "Serialization/BeamJsonUtils.h"



void URealmsBasicPromoteRealmResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void URealmsBasicPromoteRealmResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("sourcePid"), &SourcePid, Serializer);
	UBeamJsonUtils::SerializeArray<UPromotionScope*>(TEXT("scopes"), Scopes, Serializer);
}

void URealmsBasicPromoteRealmResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("sourcePid"), &SourcePid, Serializer);
	UBeamJsonUtils::SerializeArray<UPromotionScope*>(TEXT("scopes"), Scopes, Serializer);		
}

void URealmsBasicPromoteRealmResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(TEXT("sourcePid"), Bag, SourcePid, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UPromotionScope*>(TEXT("scopes"), Bag, Scopes, OuterOwner);
}



