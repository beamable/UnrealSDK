
#include "BeamableCore/Public/AutoGen/GroupSearchResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGroupSearchResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGroupSearchResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UGroup*>(TEXT("groups"), Groups, Serializer);
}

void UGroupSearchResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UGroup*>(TEXT("groups"), Groups, Serializer);		
}

void UGroupSearchResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UGroup*>(Bag->GetArrayField(TEXT("groups")), Groups, OuterOwner);
}



