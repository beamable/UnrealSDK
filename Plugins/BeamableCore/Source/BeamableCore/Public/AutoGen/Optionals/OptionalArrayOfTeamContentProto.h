#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/TeamContentProto.h"

#include "OptionalArrayOfTeamContentProto.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfTeamContentProtoLibrary.MakeOptional", BeamOptionalType="TArray<UTeamContentProto*>"))
struct BEAMABLECORE_API FOptionalArrayOfTeamContentProto : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UTeamContentProto*> Val;

	FOptionalArrayOfTeamContentProto();

	explicit FOptionalArrayOfTeamContentProto(TArray<UTeamContentProto*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};