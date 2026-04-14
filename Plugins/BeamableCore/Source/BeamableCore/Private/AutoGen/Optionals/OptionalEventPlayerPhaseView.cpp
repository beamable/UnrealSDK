
#include "BeamableCore/Public/AutoGen/Optionals/OptionalEventPlayerPhaseView.h"

FOptionalEventPlayerPhaseView::FOptionalEventPlayerPhaseView()
{
	Val = NewObject<UEventPlayerPhaseView>(GetTransientPackage());
	IsSet = false;
}

FOptionalEventPlayerPhaseView::FOptionalEventPlayerPhaseView(UEventPlayerPhaseView* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalEventPlayerPhaseView::GetAddr() const { return &Val; }

void FOptionalEventPlayerPhaseView::Set(const void* Data)
{
	Val = *((UEventPlayerPhaseView**)Data);
	IsSet = true;
}