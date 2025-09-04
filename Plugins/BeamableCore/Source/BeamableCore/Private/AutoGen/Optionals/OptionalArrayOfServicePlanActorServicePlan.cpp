
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfServicePlanActorServicePlan.h"

FOptionalArrayOfServicePlanActorServicePlan::FOptionalArrayOfServicePlanActorServicePlan()
{
	Val = TArray<UServicePlanActorServicePlan*>();
	IsSet = false;
}

FOptionalArrayOfServicePlanActorServicePlan::FOptionalArrayOfServicePlanActorServicePlan(TArray<UServicePlanActorServicePlan*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfServicePlanActorServicePlan::GetAddr() const { return &Val; }

void FOptionalArrayOfServicePlanActorServicePlan::Set(const void* Data)
{
	Val = *((TArray<UServicePlanActorServicePlan*>*)Data);
	IsSet = true;
}