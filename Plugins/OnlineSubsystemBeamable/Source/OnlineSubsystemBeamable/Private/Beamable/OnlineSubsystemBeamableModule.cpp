#include "Beamable/OnlineSubsystemBeamableModule.h"
#include "CoreMinimal.h"

#include "OnlineSubsystem.h"
#include "Beamable/OnlineSubsystemBeamable.h"
#include "Modules/ModuleManager.h"
#include "Misc/Paths.h"
#include "Misc/CommandLine.h"
#include "Modules/ModuleManager.h"
#include "OnlineSubsystemModule.h"
#include "HAL/PlatformProcess.h"

#if BEAM_ENABLE_OSS_HOOKS
#include BEAM_OSS_SUBSYSTEM_INCLUDE
#else
#define BEAM_OSS_SUBSYSTEM_IMPLEMENTATION FOnlineSubsystemBeamable
#endif

#if WITH_EDITOR
#include "Editor.h"
#endif

IMPLEMENT_MODULE(FOnlineSubsystemBeamableModule, OnlineSubsystemBeamable)

/**
 * Class responsible for creating instance(s) of the subsystem
 */
class FOnlineFactoryBeamable final : public IOnlineFactory
{
	TMap<FName, FOnlineSubsystemBeamablePtr> Instances;

public:
	FOnlineFactoryBeamable()
	{
	}

	virtual ~FOnlineFactoryBeamable()
	{
		for (TTuple<FName, TSharedPtr<FOnlineSubsystemBeamable>> Instance : Instances)
		{
			if (Instance.Value.IsValid())
			{
				Instance.Value->Shutdown();
			}
		}
		Instances.Reset();
	}

	virtual IOnlineSubsystemPtr CreateSubsystem(FName InstanceName) override
	{
		if (Instances.Contains(InstanceName))
		{
			const auto Instance = Instances[InstanceName];
			return Instance;
		}

		auto Instance = MakeShared<BEAM_OSS_SUBSYSTEM_IMPLEMENTATION, ESPMode::ThreadSafe>(InstanceName);
		if (Instance->IsEnabled())
		{
			if (!Instance->Init())
			{
				UE_LOG_ONLINE(Warning, TEXT("Beamable API failed to initialize!"));
				Instance->Shutdown();
			}
		}
		else
		{
			UE_CLOG_ONLINE(IsRunningDedicatedServer() || IsRunningGame(), Warning, TEXT("Beamable API disabled!"));
			Instance->Shutdown();
		}

		return Instance;
	}
};


#define LOCTEXT_NAMESPACE "FOnlineSubsystemBeamableModule"

void FOnlineSubsystemBeamableModule::StartupModule()
{
	BeamableFactory = new FOnlineFactoryBeamable();

	// Create and register our singleton factory with the main online subsystem for easy access
	FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
	OSS.RegisterPlatformService(BEAMABLE_SUBSYSTEM, BeamableFactory);
}

void FOnlineSubsystemBeamableModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
	OSS.UnregisterPlatformService(BEAMABLE_SUBSYSTEM);

	delete BeamableFactory;
	BeamableFactory = nullptr;
}

#undef LOCTEXT_NAMESPACE
