#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "OnlineSubsystemBeamable.h"

#include "OnlineSubsystemTypes.h"

class FOnlineSubsystemBeamableModule : public IModuleInterface
{
private:
	/** Class responsible for creating instance(s) of the subsystem */
	class FOnlineFactoryBeamable* BeamableFactory;

public:
	FOnlineSubsystemBeamableModule() : BeamableFactory(nullptr)
	{
	}

	virtual ~FOnlineSubsystemBeamableModule()
	{
	}

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual bool SupportsDynamicReloading() override
	{
		return false;
	}

	virtual bool SupportsAutomaticShutdown() override
	{
		return false;
	}
};
