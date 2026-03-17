
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/ApiSessionsHeartbeatPostSessionResponse.h"

#include "ApiSessionPostHeartbeatRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiSessionPostHeartbeatRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UApiSessionPostHeartbeatRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Session|Utils|Make/Break", DisplayName="Make ApiSessionPostHeartbeat",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiSessionPostHeartbeatRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiSessionPostHeartbeatSuccess, FBeamRequestContext, Context, UApiSessionPostHeartbeatRequest*, Request, UApiSessionsHeartbeatPostSessionResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiSessionPostHeartbeatError, FBeamRequestContext, Context, UApiSessionPostHeartbeatRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiSessionPostHeartbeatComplete, FBeamRequestContext, Context, UApiSessionPostHeartbeatRequest*, Request);

using FApiSessionPostHeartbeatFullResponse = FBeamFullResponse<UApiSessionPostHeartbeatRequest*, UApiSessionsHeartbeatPostSessionResponse*>;
DECLARE_DELEGATE_OneParam(FOnApiSessionPostHeartbeatFullResponse, FApiSessionPostHeartbeatFullResponse);
