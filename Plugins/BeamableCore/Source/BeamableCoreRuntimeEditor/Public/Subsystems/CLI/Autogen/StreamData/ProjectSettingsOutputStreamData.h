
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/SettingOutputStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ProjectSettingsOutputStreamData.generated.h"


UCLASS()
class UProjectSettingsOutputStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString ServiceName = {};
	UPROPERTY()
	TArray<USettingOutputStreamData*> Settings = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("serviceName"), ServiceName);
		UBeamJsonUtils::SerializeArray<USettingOutputStreamData*>(TEXT("settings"), Settings, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("serviceName"), ServiceName);
		UBeamJsonUtils::SerializeArray<USettingOutputStreamData*>(TEXT("settings"), Settings, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		ServiceName = Bag->GetStringField(TEXT("serviceName"));
		UBeamJsonUtils::DeserializeArray<USettingOutputStreamData*>(Bag->GetArrayField(TEXT("settings")), Settings, OuterOwner);	
	}
};


