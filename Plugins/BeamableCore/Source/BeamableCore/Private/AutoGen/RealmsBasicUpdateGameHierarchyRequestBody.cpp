
#include "BeamableCore/Public/AutoGen/RealmsBasicUpdateGameHierarchyRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void URealmsBasicUpdateGameHierarchyRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("rootPID"), &RootPID, Serializer);
	UBeamJsonUtils::SerializeArray<UProjectView*>(TEXT("projects"), Projects, Serializer);
}

void URealmsBasicUpdateGameHierarchyRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("rootPID"), &RootPID, Serializer);
	UBeamJsonUtils::SerializeArray<UProjectView*>(TEXT("projects"), Projects, Serializer);		
}

void URealmsBasicUpdateGameHierarchyRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(TEXT("rootPID"), Bag, RootPID, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UProjectView*>(TEXT("projects"), Bag, Projects, OuterOwner);
}



