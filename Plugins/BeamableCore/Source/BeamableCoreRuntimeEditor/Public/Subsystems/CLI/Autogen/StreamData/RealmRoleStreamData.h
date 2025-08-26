
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "RealmRoleStreamData.generated.h"


UCLASS(BlueprintType)
class URealmRoleStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Role = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Pid = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("role"), Role, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("pid"), Pid, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("role"), Role, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("pid"), Pid, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("role"), Bag, Role);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("pid"), Bag, Pid);	
	}
};


