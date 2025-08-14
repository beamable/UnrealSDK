
#include "BeamableCore/Public/AutoGen/Optionals/OptionalAccountPlayerView.h"

FOptionalAccountPlayerView::FOptionalAccountPlayerView()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalAccountPlayerView::FOptionalAccountPlayerView(UAccountPlayerView* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalAccountPlayerView::GetAddr() const { return &Val; }

void FOptionalAccountPlayerView::Set(const void* Data)
{
	Val = *((UAccountPlayerView**)Data);
	IsSet = true;
}