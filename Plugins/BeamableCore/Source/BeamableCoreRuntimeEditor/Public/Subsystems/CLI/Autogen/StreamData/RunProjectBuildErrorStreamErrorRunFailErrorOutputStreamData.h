
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorReportErrorRunFailErrorOutputStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorResultErrorRunFailErrorOutputStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "RunProjectBuildErrorStreamErrorRunFailErrorOutputStreamData.generated.h"


UCLASS(BlueprintType)
class URunProjectBuildErrorStreamErrorRunFailErrorOutputStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ServiceId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectErrorReportErrorRunFailErrorOutputStreamData* Report = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceId"), ServiceId, Serializer);
		UBeamJsonUtils::SerializeUObject<UProjectErrorReportErrorRunFailErrorOutputStreamData*>("report", Report, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceId"), ServiceId, Serializer);
		UBeamJsonUtils::SerializeUObject<UProjectErrorReportErrorRunFailErrorOutputStreamData*>("report", Report, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("serviceId")), ServiceId);
		UBeamJsonUtils::DeserializeUObject<UProjectErrorReportErrorRunFailErrorOutputStreamData*>("report", Bag, Report, OuterOwner);	
	}
};


