
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRealmView.h"

FOptionalArrayOfRealmView::FOptionalArrayOfRealmView()
{
	Val = TArray<URealmView*>();
	IsSet = false;
}

FOptionalArrayOfRealmView::FOptionalArrayOfRealmView(TArray<URealmView*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfRealmView::GetAddr() const { return &Val; }

void FOptionalArrayOfRealmView::Set(const void* Data)
{
	Val = *((TArray<URealmView*>*)Data);
	IsSet = true;
}