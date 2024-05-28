
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamHathoraDemoApi.h"
#include "BeamCoreSettings.h"


void UBeamHathoraDemoApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
	RequestTracker = Cast<UBeamRequestTracker>(Collection.InitializeDependency(UBeamRequestTracker::StaticClass()));
	ResponseCache = Cast<UBeamResponseCache>(Collection.InitializeDependency(UBeamResponseCache::StaticClass()));
	MicroserviceName = TEXT("HathoraDemo");
}

void UBeamHathoraDemoApi::Deinitialize()
{
	Super::Deinitialize();
}














