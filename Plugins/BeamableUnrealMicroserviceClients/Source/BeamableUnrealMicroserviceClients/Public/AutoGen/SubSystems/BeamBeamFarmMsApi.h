

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"
#include "BeamBackend/ResponseCache/BeamResponseCache.h"
#include "RequestTracker/BeamRequestTracker.h"

#include "BeamBackend/BeamMicroserviceClientSubsystem.h"

#include "BeamBeamFarmMsApi.generated.h"


/**
 * Subsystem containing request calls for the BeamFarmMs service.
 */
UCLASS(NotBlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamBeamFarmMsApi : public UBeamMicroserviceClientSubsystem
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
    
	UFUNCTION(BlueprintGetter, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Federation")
	FString GetFederatedLogin_Id_Google() const { return TEXT("google"); }

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Federation")
	void GetFederatedLogin_Data_Google(UPARAM(DisplayName="MicroserviceName") FString& MsName, UPARAM(DisplayName="FederationId") FString& Id)
	{
		MsName = GetMicroserviceName();
		Id = GetFederatedLogin_Id_Google();
	}
		
	UFUNCTION(BlueprintGetter, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Federation")
	FString GetFederatedLogin_Id_Apple() const { return TEXT("apple"); }

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Federation")
	void GetFederatedLogin_Data_Apple(UPARAM(DisplayName="MicroserviceName") FString& MsName, UPARAM(DisplayName="FederationId") FString& Id)
	{
		MsName = GetMicroserviceName();
		Id = GetFederatedLogin_Id_Apple();
	}

private:

	

	

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamBeamFarmMsApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamBeamFarmMsApi>(); }

	

	

	

	
};
