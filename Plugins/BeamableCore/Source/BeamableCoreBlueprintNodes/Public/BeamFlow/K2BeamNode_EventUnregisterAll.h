// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2BeamNode_EventRegister.h"
#include "K2BeamNode_EventUnregister.h"
#include "K2BeamNode_EventUnregisterAll.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable, NotBlueprintType, Hidden, meta=(EventRegister))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_EventUnregisterAll : public UK2BeamNode_EventUnregister
{
	GENERATED_BODY()

public:
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;

	/**
	 *  Get the menu category that will appears on the search node
	 */
	virtual FText GetMenuCategory() const override
	{
		FString Category = FString::Printf(TEXT("Beam|%s|Events"), *GetServiceName());
		return FText::FromString(Category);
	};

	//UK2Node impl
	virtual void AllocateDefaultPins() override;
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual bool CanJumpToDefinition() const override { return false; };
	virtual void JumpToDefinition() const override;
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual bool ShouldShowNodeProperties() const override { return true; }
	virtual void NodeConnectionListChanged() override;
	//BeamFlowNode impl

	/**
	 * @brief The UClass for a subsystem (GameInstanceSubsystem or BeamRuntimeSubsystem) that this function resides in. 
	 */
	virtual UClass* GetRuntimeSubsystemClass() const override;

	UClass* GetClassFromObject() const;

protected:
	/**
	 * @brief The subsystem's GetSelf function name that we can use to call a function on it.
	 * See default implementation to override it correctly.  
	 */
	virtual FName GetSubsystemSelfFunctionName() const;


	virtual bool IsValidProperty(FMulticastDelegateProperty* DelegateProp) override;
};

/***
 *      ______                          _         
 *     |  ____|                        | |        
 *     | |__    __   __   ___   _ __   | |_   ___ 
 *     |  __|   \ \ / /  / _ \ | '_ \  | __| / __|
 *     | |____   \ V /  |  __/ | | | | | |_  \__ \
 *     |______|   \_/    \___| |_| |_|  \__| |___/
 *                                                
 *                                                
 */

#define LOCTEXT_NAMESPACE "K2BeamNode_EventRegister_Object"

UCLASS(meta=(BeamEventUnregisterAll))
class UK2BeamNode_EventUnregisterAll_Object : public UK2BeamNode_EventUnregisterAll
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Object Unbind all Events"); }

protected:
	virtual bool ShouldUsesObject() override { return true; };
};
#undef LOCTEXT_NAMESPACE
