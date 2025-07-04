#pragma once
#include "BeamPIE_Settings.h"

#include "BeamPIEConfig.generated.h"

UCLASS(BlueprintType, Config=BeamPIE, meta=(DisplayName="Beamable PIE"))
class BEAMABLECORE_API UBeamPIEConfig : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	TMap<FString, FGuid> PerMapSelection;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	TArray<FBeamPIE_Settings> AllSettings;
	
	/**
	 * Set by looking at whether PIE is configured to run under one process or not.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	bool bIsRunningGameServerLocally = false;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	FString CurrLocalServerPort;

	
	
	/**
	 * Saves this as the configuration file.
	 */
	UFUNCTION(BlueprintCallable)
	void Save()
	{
		this->SaveConfig(CPF_Config);		
		UE_LOG(LogTemp, Warning, TEXT("Saved PIE Config - %d"), this->bIsRunningGameServerLocally)		
	}
};
