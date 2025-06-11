
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/SettingOutputStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ProjectSettingsOutputStreamData.generated.h"


UCLASS(BlueprintType)
class UProjectSettingsOutputStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ServiceName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USettingOutputStreamData*> Settings = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
		UBeamJsonUtils::SerializeArray<USettingOutputStreamData*>(TEXT("settings"), Settings, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
		UBeamJsonUtils::SerializeArray<USettingOutputStreamData*>(TEXT("settings"), Settings, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("serviceName")), ServiceName);
		UBeamJsonUtils::DeserializeArray<USettingOutputStreamData*>(Bag->GetArrayField(TEXT("settings")), Settings, OuterOwner);	
	}
};


