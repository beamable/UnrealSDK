// Fill out your copyright notice in the Description page of Project Settings.


#include "Hooks/BeamBaseHook.h"

void UBeamBaseHook::SetContext(const UObject* ContextReference)
{
	this->Context = ContextReference;
}
