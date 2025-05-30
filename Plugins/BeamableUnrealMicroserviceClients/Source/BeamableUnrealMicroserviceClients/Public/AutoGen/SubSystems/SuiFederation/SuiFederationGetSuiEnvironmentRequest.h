
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SuiFederationGetSuiEnvironmentResponse.h"

#include "SuiFederationGetSuiEnvironmentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API USuiFederationGetSuiEnvironmentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	USuiFederationGetSuiEnvironmentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|SuiFederation", DisplayName="Beam - Make SuiFederationGetSuiEnvironment",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static USuiFederationGetSuiEnvironmentRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnSuiFederationGetSuiEnvironmentSuccess, FBeamRequestContext, Context, USuiFederationGetSuiEnvironmentRequest*, Request, USuiFederationGetSuiEnvironmentResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnSuiFederationGetSuiEnvironmentError, FBeamRequestContext, Context, USuiFederationGetSuiEnvironmentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnSuiFederationGetSuiEnvironmentComplete, FBeamRequestContext, Context, USuiFederationGetSuiEnvironmentRequest*, Request);

using FSuiFederationGetSuiEnvironmentFullResponse = FBeamFullResponse<USuiFederationGetSuiEnvironmentRequest*, USuiFederationGetSuiEnvironmentResponse*>;
DECLARE_DELEGATE_OneParam(FOnSuiFederationGetSuiEnvironmentFullResponse, FSuiFederationGetSuiEnvironmentFullResponse);
