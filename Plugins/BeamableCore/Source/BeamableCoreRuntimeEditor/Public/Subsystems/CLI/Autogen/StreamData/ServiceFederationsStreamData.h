
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/FederationsConfigStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ServiceFederationsStreamData.generated.h"


UCLASS(BlueprintType)
class UServiceFederationsStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BeamoName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RoutingKey = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFederationsConfigStreamData* Federations = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("beamoName"), BeamoName);
		Serializer->WriteValue(TEXT("routingKey"), RoutingKey);
		UBeamJsonUtils::SerializeUObject<UFederationsConfigStreamData*>("federations", Federations, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("beamoName"), BeamoName);
		Serializer->WriteValue(TEXT("routingKey"), RoutingKey);
		UBeamJsonUtils::SerializeUObject<UFederationsConfigStreamData*>("federations", Federations, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		BeamoName = Bag->GetStringField(TEXT("beamoName"));
		RoutingKey = Bag->GetStringField(TEXT("routingKey"));
		UBeamJsonUtils::DeserializeUObject<UFederationsConfigStreamData*>("federations", Bag, Federations, OuterOwner);	
	}
};


