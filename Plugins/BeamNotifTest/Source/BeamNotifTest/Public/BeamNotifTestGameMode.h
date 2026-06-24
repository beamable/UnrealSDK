#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BeamNotifTestGameMode.generated.h"

/// Minimal game mode for the standalone notification-test level. No pawn — it just spawns
/// the test player controller, which puts the UMG test screen on the viewport.
UCLASS()
class BEAMNOTIFTEST_API ABeamNotifTestGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ABeamNotifTestGameMode();
};
