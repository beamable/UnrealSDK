
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorResultBuildErrorsStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ProjectErrorReportBuildErrorsStreamData.generated.h"


UCLASS()
class UProjectErrorReportBuildErrorsStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	bool IsSuccess = {};
	UPROPERTY()
	TArray<UProjectErrorResultBuildErrorsStreamData*> Errors = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("isSuccess"), IsSuccess);
		UBeamJsonUtils::SerializeArray<UProjectErrorResultBuildErrorsStreamData*>(TEXT("errors"), Errors, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("isSuccess"), IsSuccess);
		UBeamJsonUtils::SerializeArray<UProjectErrorResultBuildErrorsStreamData*>(TEXT("errors"), Errors, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		IsSuccess = Bag->GetBoolField(TEXT("isSuccess"));
		UBeamJsonUtils::DeserializeArray<UProjectErrorResultBuildErrorsStreamData*>(Bag->GetArrayField(TEXT("errors")), Errors, OuterOwner);	
	}
};


