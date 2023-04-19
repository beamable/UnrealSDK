
#include "BeamableCore/Public/AutoGen/CustomerView.h"
#include "Serialization/BeamJsonUtils.h"




void UCustomerView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeArray<UProjectView*>(TEXT("projects"), Projects, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
}

void UCustomerView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeArray<UProjectView*>(TEXT("projects"), Projects, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);		
}

void UCustomerView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<int64>(Bag->TryGetField(TEXT("cid")), Cid, OuterOwner);
	Name = Bag->GetStringField(TEXT("name"));
	UBeamJsonUtils::DeserializeArray<UProjectView*>(Bag->GetArrayField(TEXT("projects")), Projects, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("alias", Bag, Alias, OuterOwner);
}



