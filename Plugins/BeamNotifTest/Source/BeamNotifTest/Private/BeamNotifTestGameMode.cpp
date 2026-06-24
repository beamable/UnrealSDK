#include "BeamNotifTestGameMode.h"
#include "BeamNotifTestPlayerController.h"

ABeamNotifTestGameMode::ABeamNotifTestGameMode()
{
    PlayerControllerClass = ABeamNotifTestPlayerController::StaticClass();
    DefaultPawnClass = nullptr; // UI-only test; no pawn needed.
}
