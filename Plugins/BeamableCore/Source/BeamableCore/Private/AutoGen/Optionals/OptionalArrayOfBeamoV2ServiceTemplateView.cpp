
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceTemplateView.h"

FOptionalArrayOfBeamoV2ServiceTemplateView::FOptionalArrayOfBeamoV2ServiceTemplateView()
{
	Val = TArray<UBeamoV2ServiceTemplateView*>();
	IsSet = false;
}

FOptionalArrayOfBeamoV2ServiceTemplateView::FOptionalArrayOfBeamoV2ServiceTemplateView(TArray<UBeamoV2ServiceTemplateView*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoV2ServiceTemplateView::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoV2ServiceTemplateView::Set(const void* Data)
{
	Val = *((TArray<UBeamoV2ServiceTemplateView*>*)Data);
	IsSet = true;
}