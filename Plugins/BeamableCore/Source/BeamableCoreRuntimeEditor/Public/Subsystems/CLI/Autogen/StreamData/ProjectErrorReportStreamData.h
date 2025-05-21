
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorResultStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ProjectErrorReportStreamData.generated.h"


UCLASS(BlueprintType)
class UProjectErrorReportStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSuccess = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UProjectErrorResultStreamData*> Errors = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("isSuccess"), IsSuccess, Serializer);
		UBeamJsonUtils::SerializeArray<UProjectErrorResultStreamData*>(TEXT("errors"), Errors, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("isSuccess"), IsSuccess, Serializer);
		UBeamJsonUtils::SerializeArray<UProjectErrorResultStreamData*>(TEXT("errors"), Errors, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isSuccess")), IsSuccess);
		UBeamJsonUtils::DeserializeArray<UProjectErrorResultStreamData*>(Bag->GetArrayField(TEXT("errors")), Errors, OuterOwner);	
	}
};


