
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/InventoryProxySettings.h"

#include "OptionalInventoryProxySettings.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalInventoryProxySettingsLibrary.MakeOptionalInventoryProxySettings"))
struct FOptionalInventoryProxySettings : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	UInventoryProxySettings* Val;

	FOptionalInventoryProxySettings();

	explicit FOptionalInventoryProxySettings(UInventoryProxySettings* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};