
#include "BeamableCore/Public/AutoGen/AccountPortalView.h"
#include "Serialization/BeamJsonUtils.h"



void UAccountPortalView::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAccountPortalView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("scopes"), Scopes, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("thirdPartyAppAssociations"), ThirdPartyAppAssociations, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("roleString"), &RoleString, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamExternalIdentity>, FBeamExternalIdentity>(TEXT("external"), &External, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URoleMapping*>, URoleMapping*>(TEXT("roles"), &Roles, Serializer);
}

void UAccountPortalView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("scopes"), Scopes, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("thirdPartyAppAssociations"), ThirdPartyAppAssociations, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("roleString"), &RoleString, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamExternalIdentity>, FBeamExternalIdentity>(TEXT("external"), &External, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URoleMapping*>, URoleMapping*>(TEXT("roles"), &Roles, Serializer);		
}

void UAccountPortalView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<int64>(Bag->TryGetField(TEXT("id")), Id, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("scopes")), Scopes, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("thirdPartyAppAssociations")), ThirdPartyAppAssociations, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("email", Bag, Email, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("roleString", Bag, RoleString, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("language", Bag, Language, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FBeamExternalIdentity>, FBeamExternalIdentity>("external", Bag, External, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<URoleMapping*>, URoleMapping*>("roles", Bag, Roles, OuterOwner);
}



