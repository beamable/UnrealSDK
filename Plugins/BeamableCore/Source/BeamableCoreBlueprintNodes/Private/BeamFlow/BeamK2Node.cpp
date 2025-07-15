// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamFlow/BeamK2Node.h"

#include "SourceCodeNavigation.h"


FName UBeamK2Node::GetSubsystemSelfFunctionName() const
{
	return FName("K2BeamNode_GetState");
}

FName UBeamK2Node::GetFunctionName() const
{
	return FName("K2BeamNode_GetState");
}

UClass* UBeamK2Node::GetRuntimeSubsystemClass() const
{
	return UClass::StaticClass();
}

void UBeamK2Node::JumpToDefinition() const
{
	const auto Function = GetRuntimeSubsystemClass()->FindFunctionByName(GetFunctionName());

	if (!Function) return;

	FSourceCodeNavigation::NavigateToFunction(Function);
}
