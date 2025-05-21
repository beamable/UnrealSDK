
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "AccountMeExternalIdentityStreamData.generated.h"


UCLASS(BlueprintType)
class UAccountMeExternalIdentityStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ProviderNamespace = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ProviderService = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UserId = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("providerNamespace"), ProviderNamespace, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("providerService"), ProviderService, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("userId"), UserId, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("providerNamespace"), ProviderNamespace, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("providerService"), ProviderService, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("userId"), UserId, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("providerNamespace")), ProviderNamespace);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("providerService")), ProviderService);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("userId")), UserId);	
	}
};


