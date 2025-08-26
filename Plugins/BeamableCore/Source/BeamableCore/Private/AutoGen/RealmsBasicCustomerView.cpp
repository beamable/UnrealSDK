
#include "BeamableCore/Public/AutoGen/RealmsBasicCustomerView.h"
#include "Serialization/BeamJsonUtils.h"




void URealmsBasicCustomerView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeArray<UProjectView*>(TEXT("projects"), Projects, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
}

void URealmsBasicCustomerView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeArray<UProjectView*>(TEXT("projects"), Projects, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);		
}

void URealmsBasicCustomerView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<int64>(TEXT("cid"), Bag, Cid, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeArray<UProjectView*>(TEXT("projects"), Bag, Projects, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("alias", Bag, Alias, OuterOwner);
}



