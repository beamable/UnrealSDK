
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "FederationInstanceStreamData.generated.h"


UCLASS(BlueprintType)
class UFederationInstanceStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FederationId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> FederationTypes = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> LocalSettings = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("FederationId"), FederationId);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("FederationTypes"), FederationTypes, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("LocalSettings"), LocalSettings, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("FederationId"), FederationId);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("FederationTypes"), FederationTypes, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("LocalSettings"), LocalSettings, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		FederationId = Bag->GetStringField(TEXT("FederationId"));
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("FederationTypes")), FederationTypes, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("LocalSettings")), LocalSettings, OuterOwner);	
	}
};


