#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/RealmView.h"

#include "OptionalArrayOfRealmView.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfRealmViewLibrary.MakeOptional", BeamOptionalType="TArray<URealmView*>"))
struct BEAMABLECORE_API FOptionalArrayOfRealmView : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<URealmView*> Val;

	FOptionalArrayOfRealmView();

	explicit FOptionalArrayOfRealmView(TArray<URealmView*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};