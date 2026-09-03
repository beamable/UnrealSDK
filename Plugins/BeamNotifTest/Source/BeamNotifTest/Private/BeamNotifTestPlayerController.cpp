#include "BeamNotifTestPlayerController.h"
#include "BeamNotifTestWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

ABeamNotifTestPlayerController::ABeamNotifTestPlayerController()
{
    bShowMouseCursor = true;
}

void ABeamNotifTestPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (!IsLocalController())
    {
        return;
    }

    TestWidget = CreateWidget<UBeamNotifTestWidget>(this, UBeamNotifTestWidget::StaticClass());
    if (TestWidget)
    {
        TestWidget->AddToViewport();
    }

    FInputModeGameAndUI InputMode;
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    SetInputMode(InputMode);
    bShowMouseCursor = true;
}
