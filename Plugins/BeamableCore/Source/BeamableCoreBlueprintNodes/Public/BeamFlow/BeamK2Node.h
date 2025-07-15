// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "BeamK2Node.generated.h"

/**
 * 
 */
UCLASS()
class BEAMABLECOREBLUEPRINTNODES_API UBeamK2Node : public UK2Node
{
	GENERATED_BODY()

public:
	/**
	 * @brief The UClass for a subsystem (GameInstanceSubsystem or BeamRuntimeSubsystem) that this function resides in. 
	 */
	virtual UClass* GetRuntimeSubsystemClass() const;

protected:
	virtual bool CanJumpToDefinition() const override { return true; };
	virtual void JumpToDefinition() const override;

	/**
	 * @brief The subsystem's GetSelf function name that we can use to call a function on it.
	 * See default implementation to override it correctly.  
	 */
	virtual FName GetSubsystemSelfFunctionName() const;

	/**
	 * @brief The subsystem's function.
	 */
	virtual FName GetFunctionName() const;
};
