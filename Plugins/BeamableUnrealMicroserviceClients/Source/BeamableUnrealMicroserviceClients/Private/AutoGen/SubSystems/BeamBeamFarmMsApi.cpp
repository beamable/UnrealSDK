
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamCoreSettings.h"


void UBeamBeamFarmMsApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
	RequestTracker = Cast<UBeamRequestTracker>(Collection.InitializeDependency(UBeamRequestTracker::StaticClass()));
	ResponseCache = Cast<UBeamResponseCache>(Collection.InitializeDependency(UBeamResponseCache::StaticClass()));
	MicroserviceName = TEXT("BeamFarmMs");
}

void UBeamBeamFarmMsApi::Deinitialize()
{
	Super::Deinitialize();
}














