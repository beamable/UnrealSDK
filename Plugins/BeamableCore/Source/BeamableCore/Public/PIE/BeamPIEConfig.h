#pragma once
#include "BeamPIE_Settings.h"

#include "BeamPIEConfig.generated.h"

UCLASS(BlueprintType, Config=BeamPIE, DefaultConfig, meta=(DisplayName="Beamable PIE"))
class BEAMABLECORE_API UBeamPIEConfig : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	FGuid SelectedSettingsId;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	TArray<FBeamPIE_Settings> AllSettings;

	/**
	 * Saves this as the configuration file.
	 */
	UFUNCTION(BlueprintCallable)
	void Save() { this->SaveConfig(CPF_Config, *this->GetDefaultConfigFilename()); }
};
