#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#include "OptionalArrayOfLobby.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfLobbyLibrary.MakeOptional", BeamOptionalType="TArray<ULobby*>"))
struct BEAMABLECORE_API FOptionalArrayOfLobby : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<ULobby*> Val;

	FOptionalArrayOfLobby();

	explicit FOptionalArrayOfLobby(TArray<ULobby*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};