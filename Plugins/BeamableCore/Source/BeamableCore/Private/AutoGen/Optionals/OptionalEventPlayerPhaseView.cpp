
#include "BeamableCore/Public/AutoGen/Optionals/OptionalEventPlayerPhaseView.h"

FOptionalEventPlayerPhaseView::FOptionalEventPlayerPhaseView()
{
	Val = nullptr;
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