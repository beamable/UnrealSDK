#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BeamNotifTestPlayerController.generated.h"

class UBeamNotifTestWidget;

UCLASS()
class BEAMNOTIFTEST_API ABeamNotifTestPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ABeamNotifTestPlayerController();

protected:
    virtual void BeginPlay() override;

    UPROPERTY()
    UBeamNotifTestWidget* TestWidget = nullptr;
};
