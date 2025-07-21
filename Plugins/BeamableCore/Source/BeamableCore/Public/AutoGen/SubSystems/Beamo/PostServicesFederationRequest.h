
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/BeamoV2ServiceRegistrationQuery.h"
#include "BeamableCore/Public/AutoGen/BeamoV2FederationRegistrationResponse.h"

#include "PostServicesFederationRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostServicesFederationRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBeamoV2ServiceRegistrationQuery* Body = {};

	// Beam Base Request Declaration
	UPostServicesFederationRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PostServicesFederation",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bLocalOnly,_ServiceName,_RoutingKey,_Federation,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostServicesFederationRequest* Make(FOptionalBool _bLocalOnly, FOptionalString _ServiceName, FOptionalString _RoutingKey, FOptionalBeamoV2SupportedFederation _Federation, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostServicesFederationSuccess, FBeamRequestContext, Context, UPostServicesFederationRequest*, Request, UBeamoV2FederationRegistrationResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostServicesFederationError, FBeamRequestContext, Context, UPostServicesFederationRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostServicesFederationComplete, FBeamRequestContext, Context, UPostServicesFederationRequest*, Request);

using FPostServicesFederationFullResponse = FBeamFullResponse<UPostServicesFederationRequest*, UBeamoV2FederationRegistrationResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostServicesFederationFullResponse, FPostServicesFederationFullResponse);
