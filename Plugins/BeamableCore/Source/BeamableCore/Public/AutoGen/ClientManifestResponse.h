#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamCsvUtils.h"

#include "ClientManifestResponse.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UClientManifestResponse : public UObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	UDataTable* CsvData;

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;
};