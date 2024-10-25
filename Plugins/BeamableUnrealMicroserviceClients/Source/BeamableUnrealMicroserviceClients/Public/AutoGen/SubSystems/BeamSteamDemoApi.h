

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"
#include "BeamBackend/ResponseCache/BeamResponseCache.h"
#include "RequestTracker/BeamRequestTracker.h"

#include "BeamBackend/BeamMicroserviceClientSubsystem.h"

#include "BeamSteamDemoApi.generated.h"


/**
 * Subsystem containing request calls for the SteamDemo service.
 */
UCLASS(NotBlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamSteamDemoApi : public UBeamMicroserviceClientSubsystem
{
private:
	GENERATED_BODY()
	/** @brief Initializes the auto-increment Id and binds the ExecuteRequestDelegate to DefaultExecuteRequestImpl  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Cleans up the system.  */
	virtual void Deinitialize() override;

	UPROPERTY()
	UBeamBackend* Backend;

	UPROPERTY()
	UBeamRequestTracker* RequestTracker;

	UPROPERTY()
	UBeamResponseCache* ResponseCache;

	

	

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamSteamDemoApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamSteamDemoApi>(); }

	

	

	

	
};
