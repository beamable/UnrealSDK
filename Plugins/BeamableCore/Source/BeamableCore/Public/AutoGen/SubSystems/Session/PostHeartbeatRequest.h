
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/SessionHeartbeat.h"

#include "PostHeartbeatRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostHeartbeatRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UPostHeartbeatRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Session|Utils|Make/Break", DisplayName="Make PostHeartbeat",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostHeartbeatRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostHeartbeatSuccess, FBeamRequestContext, Context, UPostHeartbeatRequest*, Request, USessionHeartbeat*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostHeartbeatError, FBeamRequestContext, Context, UPostHeartbeatRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostHeartbeatComplete, FBeamRequestContext, Context, UPostHeartbeatRequest*, Request);

using FPostHeartbeatFullResponse = FBeamFullResponse<UPostHeartbeatRequest*, USessionHeartbeat*>;
DECLARE_DELEGATE_OneParam(FOnPostHeartbeatFullResponse, FPostHeartbeatFullResponse);
