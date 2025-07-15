// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamFlow/K2BeamNode.h"

#include "SourceCodeNavigation.h"


FName UK2BeamNode::GetSubsystemSelfFunctionName() const
{
	return FName("K2BeamNode_GetState");
}

FName UK2BeamNode::GetFunctionName() const
{
	return FName("K2BeamNode_GetState");
}

UClass* UK2BeamNode::GetRuntimeSubsystemClass() const
{
	return UClass::StaticClass();
}

void UK2BeamNode::JumpToDefinition() const
{
	const auto Function = GetRuntimeSubsystemClass()->FindFunctionByName(GetFunctionName());

	if (!Function) return;

	FSourceCodeNavigation::NavigateToFunction(Function);
}
