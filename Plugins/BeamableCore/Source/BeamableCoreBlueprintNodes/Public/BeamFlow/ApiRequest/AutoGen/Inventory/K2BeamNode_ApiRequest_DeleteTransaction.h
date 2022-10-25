
#pragma once

#include "CoreMinimal.h"
#include "BeamFlow/ApiRequest/K2BeamNode_ApiRequest.h"

#include "K2BeamNode_ApiRequest_DeleteTransaction.generated.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteTransaction"

/**
* This is the code-gen'ed declaration for the Beam Flow's Endpoint: Delete /object/inventory/{objectId}/transaction  of the Inventory Service. 
*/
UCLASS(meta=(BeamFlow))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_ApiRequest_DeleteTransaction : public UK2BeamNode_ApiRequest
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
