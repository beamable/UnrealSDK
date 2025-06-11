
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorResultBuildErrorsStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ProjectErrorReportBuildErrorsStreamData.generated.h"


UCLASS(BlueprintType)
class UProjectErrorReportBuildErrorsStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSuccess = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UProjectErrorResultBuildErrorsStreamData*> Errors = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("isSuccess"), IsSuccess, Serializer);
		UBeamJsonUtils::SerializeArray<UProjectErrorResultBuildErrorsStreamData*>(TEXT("errors"), Errors, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("isSuccess"), IsSuccess, Serializer);
		UBeamJsonUtils::SerializeArray<UProjectErrorResultBuildErrorsStreamData*>(TEXT("errors"), Errors, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isSuccess")), IsSuccess);
		UBeamJsonUtils::DeserializeArray<UProjectErrorResultBuildErrorsStreamData*>(Bag->GetArrayField(TEXT("errors")), Errors, OuterOwner);	
	}
};


