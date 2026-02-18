

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
	/** @brief Initializes the auto-increment Id */
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
    
	UFUNCTION(BlueprintGetter, BlueprintInternalUseOnly, Category="Beam|SteamDemo|Utils|Federation")
	FString GetFederatedPlayerInit_Id_Default() const { return TEXT("default"); }

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|SteamDemo|Utils|Federation")
	void GetFederatedPlayerInit_Data_Default(UPARAM(DisplayName="MicroserviceName") FString& MsName, UPARAM(DisplayName="FederationId") FString& Id)
	{
		MsName = GetMicroserviceName();
		Id = GetFederatedPlayerInit_Id_Default();
	}
		
	UFUNCTION(BlueprintGetter, BlueprintInternalUseOnly, Category="Beam|SteamDemo|Utils|Federation")
	FString GetFederatedLogin_Id_Steam() const { return TEXT("steam"); }

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|SteamDemo|Utils|Federation")
	void GetFederatedLogin_Data_Steam(UPARAM(DisplayName="MicroserviceName") FString& MsName, UPARAM(DisplayName="FederationId") FString& Id)
	{
		MsName = GetMicroserviceName();
		Id = GetFederatedLogin_Id_Steam();
	}

private:

	

	

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamSteamDemoApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamSteamDemoApi>(); }

	

	

	

	
};
