
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/SessionHeartbeat.h"

#include "BasicSessionPostHeartbeatRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicSessionPostHeartbeatRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBasicSessionPostHeartbeatRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Session|Utils|Make/Break", DisplayName="Make BasicSessionPostHeartbeat",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicSessionPostHeartbeatRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicSessionPostHeartbeatSuccess, FBeamRequestContext, Context, UBasicSessionPostHeartbeatRequest*, Request, USessionHeartbeat*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicSessionPostHeartbeatError, FBeamRequestContext, Context, UBasicSessionPostHeartbeatRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicSessionPostHeartbeatComplete, FBeamRequestContext, Context, UBasicSessionPostHeartbeatRequest*, Request);

using FBasicSessionPostHeartbeatFullResponse = FBeamFullResponse<UBasicSessionPostHeartbeatRequest*, USessionHeartbeat*>;
DECLARE_DELEGATE_OneParam(FOnBasicSessionPostHeartbeatFullResponse, FBasicSessionPostHeartbeatFullResponse);
