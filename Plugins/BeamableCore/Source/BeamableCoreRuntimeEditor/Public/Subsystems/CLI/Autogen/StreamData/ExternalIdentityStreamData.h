
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ExternalIdentityStreamData.generated.h"


UCLASS()
class UExternalIdentityStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString ProviderNamespace = {};
	UPROPERTY()
	FString ProviderService = {};
	UPROPERTY()
	FString UserId = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("providerNamespace"), ProviderNamespace);
		Serializer->WriteValue(TEXT("providerService"), ProviderService);
		Serializer->WriteValue(TEXT("userId"), UserId);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("providerNamespace"), ProviderNamespace);
		Serializer->WriteValue(TEXT("providerService"), ProviderService);
		Serializer->WriteValue(TEXT("userId"), UserId);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		ProviderNamespace = Bag->GetStringField(TEXT("providerNamespace"));
		ProviderService = Bag->GetStringField(TEXT("providerService"));
		UserId = Bag->GetStringField(TEXT("userId"));	
	}
};


