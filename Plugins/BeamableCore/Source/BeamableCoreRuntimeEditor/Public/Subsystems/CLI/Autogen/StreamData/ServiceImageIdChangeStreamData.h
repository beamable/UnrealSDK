
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ServiceImageIdChangeStreamData.generated.h"


UCLASS()
class UServiceImageIdChangeStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Service = {};
	UPROPERTY()
	FString OldImageId = {};
	UPROPERTY()
	FString NextImageId = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("oldImageId"), OldImageId);
		Serializer->WriteValue(TEXT("nextImageId"), NextImageId);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("oldImageId"), OldImageId);
		Serializer->WriteValue(TEXT("nextImageId"), NextImageId);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Service = Bag->GetStringField(TEXT("service"));
		OldImageId = Bag->GetStringField(TEXT("oldImageId"));
		NextImageId = Bag->GetStringField(TEXT("nextImageId"));	
	}
};


