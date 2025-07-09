
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfServiceTemplateView.h"

FOptionalArrayOfServiceTemplateView::FOptionalArrayOfServiceTemplateView()
{
	Val = TArray<UServiceTemplateView*>();
	IsSet = false;
}

FOptionalArrayOfServiceTemplateView::FOptionalArrayOfServiceTemplateView(TArray<UServiceTemplateView*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfServiceTemplateView::GetAddr() const { return &Val; }

void FOptionalArrayOfServiceTemplateView::Set(const void* Data)
{
	Val = *((TArray<UServiceTemplateView*>*)Data);
	IsSet = true;
}