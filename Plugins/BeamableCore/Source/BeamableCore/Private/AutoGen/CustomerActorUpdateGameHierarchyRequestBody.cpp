
#include "BeamableCore/Public/AutoGen/CustomerActorUpdateGameHierarchyRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UCustomerActorUpdateGameHierarchyRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<URealmView*>(TEXT("realms"), Realms, Serializer);
}

void UCustomerActorUpdateGameHierarchyRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<URealmView*>(TEXT("realms"), Realms, Serializer);		
}

void UCustomerActorUpdateGameHierarchyRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<URealmView*>(TEXT("realms"), Bag, Realms, OuterOwner);
}



