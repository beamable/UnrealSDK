// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KismetCompiler.h"
#include "K2Node_CallFunction.h"
#include "BeamFlow/ExecuteRequest/K2BeamNode_ApiRequest.h"

#include "K2BeamNode_ApiRequest_BasicAccountsGetMe.generated.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ExecuteRequest_BasicAccountsGetMe"


/**
 * 
 */
UCLASS(meta=(BeamFlow))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_ApiRequest_BasicAccountsGetMe : public UK2BeamNode_ApiRequest
{
	GENERATED_BODY()
public:
	virtual FName GetSelfFunctionName() const override;
	virtual FName GetRequestFunctionName() const override;
	virtual FName GetMakeFunctionName() const override;
	virtual FString GetServiceName() const override;
	virtual FString GetEndpointName() const override;
	virtual UClass* GetApiClass() const override;
	virtual UClass* GetRequestClass() const override;
	virtual UClass* GetResponseClass() const override;
	virtual FString GetRequestSuccessDelegateName() const override;
	virtual FString GetRequestErrorDelegateName() const override;
	virtual FString GetRequestCompleteDelegateName() const override;
};

#undef LOCTEXT_NAMESPACE
