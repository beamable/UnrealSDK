
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMetadataView.h"

FOptionalMetadataView::FOptionalMetadataView()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalMetadataView::FOptionalMetadataView(UMetadataView* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalMetadataView::GetAddr() const { return &Val; }

void FOptionalMetadataView::Set(const void* Data)
{
	Val = *((UMetadataView**)Data);
	IsSet = true;
}