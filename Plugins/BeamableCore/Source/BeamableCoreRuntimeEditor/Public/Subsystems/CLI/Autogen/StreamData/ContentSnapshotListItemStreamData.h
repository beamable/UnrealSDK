
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ContentSnapshotListItemStreamData.generated.h"


UCLASS(BlueprintType)
class UContentSnapshotListItemStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentStatus = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Name"), Name, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CurrentStatus"), CurrentStatus, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Name"), Name, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CurrentStatus"), CurrentStatus, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Name"), Bag, Name);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("CurrentStatus"), Bag, CurrentStatus);	
	}
};


