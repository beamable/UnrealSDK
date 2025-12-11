#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/TagList.h"

#include "OptionalMapOfTagList.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalMapOfTagListLibrary.MakeOptional", BeamOptionalType="TMap<FString, UTagList*>"))
struct BEAMABLECORE_API FOptionalMapOfTagList : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<FString, UTagList*> Val;

	FOptionalMapOfTagList();

	explicit FOptionalMapOfTagList(TMap<FString, UTagList*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};