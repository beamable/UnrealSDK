#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/LobbyPlayer.h"

#include "OptionalArrayOfLobbyPlayer.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfLobbyPlayerLibrary.MakeOptional", BeamOptionalType="TArray<ULobbyPlayer*>"))
struct BEAMABLECORE_API FOptionalArrayOfLobbyPlayer : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	TArray<ULobbyPlayer*> Val;

	FOptionalArrayOfLobbyPlayer();

	explicit FOptionalArrayOfLobbyPlayer(TArray<ULobbyPlayer*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};