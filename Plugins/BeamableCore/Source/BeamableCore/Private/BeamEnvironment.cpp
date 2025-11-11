// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamEnvironment.h"

#include "BeamCoreSettings.h"
#include "Engine/AssetManager.h"

const FString RUNTIME_BEAM_ENVIRONMENT = FString::Printf(TEXT("BeamEnvironmentData:Runtime"));
const FString EDITOR_BEAM_ENVIRONMENT = FString::Printf(TEXT("BeamEnvironmentData:Editor"));


void UBeamEnvironmentData::Serialize(FJsonSerializerBase& Serializer, bool bFlatObject)
{
	Serializer.StartObject();
	Serializer.Serialize(TEXT("host"), APIUrl);
	Serializer.EndObject();
}

void UBeamEnvironment::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UBeamEnvironment::Deinitialize()
{
}

FString UBeamEnvironment::GetAPIUrl()
{
	if (!Data)
	{
		const UBeamCoreSettings* beamCoreSettings = GetDefault<UBeamCoreSettings>();
		Data = beamCoreSettings->BeamableEnvironment.LoadSynchronous();
	}

	return Data->APIUrl;
}

bool UBeamEnvironment::RefreshEnvData()
{
	const UBeamCoreSettings* beamCoreSettings = GetDefault<UBeamCoreSettings>();
	if (!Data)
	{
		Data = beamCoreSettings->BeamableEnvironment.LoadSynchronous();
		return true;
	}
	else
	{
		auto NewData = beamCoreSettings->BeamableEnvironment.LoadSynchronous();

		if (NewData && NewData->APIUrl != Data->APIUrl)
		{
			Data = NewData;
			return true;
		}
	}
	return false;
}

void UBeamEnvironment::PullRoutesConfig(UBeamEnvironmentData* EnvData)
{
	OnRefreshBackendAsset.ExecuteIfBound(EnvData);
}

void UBeamEnvironmentData::RefreshBackendDataAsset()
{
	GEngine->GetEngineSubsystem<UBeamEnvironment>()->PullRoutesConfig(this);
}
