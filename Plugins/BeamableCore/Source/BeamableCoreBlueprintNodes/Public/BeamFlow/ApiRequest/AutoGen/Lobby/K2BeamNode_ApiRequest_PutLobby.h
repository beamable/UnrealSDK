
#pragma once

#include "CoreMinimal.h"
#include "BeamFlow/ApiRequest/K2BeamNode_ApiRequest.h"

#include "K2BeamNode_ApiRequest_PutLobby.generated.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutLobby"

/**
* This is the code-gen'ed declaration for the Beam Flow's Endpoint: Put /api/lobbies/{id}  of the Lobby Service. 
*/
UCLASS(meta=(BeamFlow))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_ApiRequest_PutLobby : public UK2BeamNode_ApiRequest
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
