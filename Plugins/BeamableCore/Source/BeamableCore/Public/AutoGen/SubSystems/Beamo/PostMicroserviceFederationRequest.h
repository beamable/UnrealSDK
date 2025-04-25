
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/MicroserviceRegistrationsQuery.h"
#include "BeamableCore/Public/AutoGen/SupportedFederationsResponse.h"

#include "PostMicroserviceFederationRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostMicroserviceFederationRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UMicroserviceRegistrationsQuery* Body = {};

	// Beam Base Request Declaration
	UPostMicroserviceFederationRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PostMicroserviceFederation",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bLocalOnly,_ServiceName,_RoutingKey,_Federation,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostMicroserviceFederationRequest* Make(FOptionalBool _bLocalOnly, FOptionalString _ServiceName, FOptionalString _RoutingKey, FOptionalSupportedFederation _Federation, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostMicroserviceFederationSuccess, FBeamRequestContext, Context, UPostMicroserviceFederationRequest*, Request, USupportedFederationsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostMicroserviceFederationError, FBeamRequestContext, Context, UPostMicroserviceFederationRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostMicroserviceFederationComplete, FBeamRequestContext, Context, UPostMicroserviceFederationRequest*, Request);

using FPostMicroserviceFederationFullResponse = FBeamFullResponse<UPostMicroserviceFederationRequest*, USupportedFederationsResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostMicroserviceFederationFullResponse, FPostMicroserviceFederationFullResponse);
