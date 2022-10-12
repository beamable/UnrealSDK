
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/DatabaseMeasurement.h"

#include "OptionalArrayOfDatabaseMeasurement.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalArrayOfDatabaseMeasurementLibrary.MakeOptionalArrayOfDatabaseMeasurement"))
struct FOptionalArrayOfDatabaseMeasurement : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<UDatabaseMeasurement*> Val;

	FOptionalArrayOfDatabaseMeasurement();

	explicit FOptionalArrayOfDatabaseMeasurement(TArray<UDatabaseMeasurement*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};