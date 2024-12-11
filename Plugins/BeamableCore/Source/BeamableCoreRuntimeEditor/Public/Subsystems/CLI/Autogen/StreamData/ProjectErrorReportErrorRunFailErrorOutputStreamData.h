
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorResultErrorRunFailErrorOutputStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ProjectErrorReportErrorRunFailErrorOutputStreamData.generated.h"


UCLASS(BlueprintType)
class UProjectErrorReportErrorRunFailErrorOutputStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSuccess = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UProjectErrorResultErrorRunFailErrorOutputStreamData*> Errors = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("isSuccess"), IsSuccess);
		UBeamJsonUtils::SerializeArray<UProjectErrorResultErrorRunFailErrorOutputStreamData*>(TEXT("errors"), Errors, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("isSuccess"), IsSuccess);
		UBeamJsonUtils::SerializeArray<UProjectErrorResultErrorRunFailErrorOutputStreamData*>(TEXT("errors"), Errors, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		IsSuccess = Bag->GetBoolField(TEXT("isSuccess"));
		UBeamJsonUtils::DeserializeArray<UProjectErrorResultErrorRunFailErrorOutputStreamData*>(Bag->GetArrayField(TEXT("errors")), Errors, OuterOwner);	
	}
};


