// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BeamBaseHook.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BEAMABLECORERUNTIME_API UBeamBaseHook : public UObject
{
	GENERATED_BODY()

	UWorld* GetWorld() const override
	{
		if (IsTemplate() || !GetOuter())
		{
			return nullptr;
		}
		return Context->GetWorld();
	}

public:
	const UObject* Context;
	
	virtual void SetContext(const UObject* ContextReference);
};
