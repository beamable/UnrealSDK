#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Realm.h"

#include "OptionalArrayOfRealm.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfRealmLibrary.MakeOptional", BeamOptionalType="TArray<URealm*>"))
struct BEAMABLECORE_API FOptionalArrayOfRealm : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<URealm*> Val;

	FOptionalArrayOfRealm();

	explicit FOptionalArrayOfRealm(TArray<URealm*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};