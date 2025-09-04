

#include "AutoGen/Optionals/OptionalArrayOfServicePlanActorServicePlanLibrary.h"

FOptionalArrayOfServicePlanActorServicePlan UOptionalArrayOfServicePlanActorServicePlanLibrary::MakeOptional(TArray<UServicePlanActorServicePlan*> Value)
{
	FOptionalArrayOfServicePlanActorServicePlan Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfServicePlanActorServicePlan UOptionalArrayOfServicePlanActorServicePlanLibrary::Conv_OptionalFromValue(TArray<UServicePlanActorServicePlan*> Value)
{
	FOptionalArrayOfServicePlanActorServicePlan Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfServicePlanActorServicePlanLibrary::HasValue(const FOptionalArrayOfServicePlanActorServicePlan& Optional, TArray<UServicePlanActorServicePlan*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UServicePlanActorServicePlan*> UOptionalArrayOfServicePlanActorServicePlanLibrary::GetOptionalValue(const FOptionalArrayOfServicePlanActorServicePlan& Optional, TArray<UServicePlanActorServicePlan*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

