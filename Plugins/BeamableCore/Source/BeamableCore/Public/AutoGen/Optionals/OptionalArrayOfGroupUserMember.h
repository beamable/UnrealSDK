#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/GroupUserMember.h"

#include "OptionalArrayOfGroupUserMember.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfGroupUserMemberLibrary.MakeOptional", BeamOptionalType="TArray<UGroupUserMember*>"))
struct BEAMABLECORE_API FOptionalArrayOfGroupUserMember : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UGroupUserMember*> Val;

	FOptionalArrayOfGroupUserMember();

	explicit FOptionalArrayOfGroupUserMember(TArray<UGroupUserMember*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};