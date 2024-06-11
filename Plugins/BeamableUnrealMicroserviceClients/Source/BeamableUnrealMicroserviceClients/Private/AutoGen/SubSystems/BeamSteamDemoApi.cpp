
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamSteamDemoApi.h"
#include "BeamCoreSettings.h"


void UBeamSteamDemoApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
	RequestTracker = Cast<UBeamRequestTracker>(Collection.InitializeDependency(UBeamRequestTracker::StaticClass()));
	ResponseCache = Cast<UBeamResponseCache>(Collection.InitializeDependency(UBeamResponseCache::StaticClass()));
	MicroserviceName = TEXT("SteamDemo");
}

void UBeamSteamDemoApi::Deinitialize()
{
	Super::Deinitialize();
}














