
#include "BeamableCore/Public/AutoGen/UpdateGameHierarchyRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UUpdateGameHierarchyRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("rootPID"), &RootPID, Serializer);
	UBeamJsonUtils::SerializeArray<UProjectView*>(TEXT("projects"), Projects, Serializer);
}

void UUpdateGameHierarchyRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("rootPID"), &RootPID, Serializer);
	UBeamJsonUtils::SerializeArray<UProjectView*>(TEXT("projects"), Projects, Serializer);		
}

void UUpdateGameHierarchyRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(TEXT("rootPID"), Bag, RootPID, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UProjectView*>(TEXT("projects"), Bag, Projects, OuterOwner);
}



