
#include "BeamableCore/Public/AutoGen/GetGameResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetGameResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetGameResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UProjectView*>(TEXT("projects"), Projects, Serializer);
}

void UGetGameResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UProjectView*>(TEXT("projects"), Projects, Serializer);		
}

void UGetGameResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UProjectView*>(Bag->GetArrayField(TEXT("projects")), Projects, OuterOwner);
}



