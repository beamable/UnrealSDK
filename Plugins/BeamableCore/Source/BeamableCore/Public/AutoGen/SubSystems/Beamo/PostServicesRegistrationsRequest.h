
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/ServiceRegistrationQuery.h"
#include "BeamableCore/Public/AutoGen/ServiceRegistrationResponse.h"

#include "PostServicesRegistrationsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostServicesRegistrationsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UServiceRegistrationQuery* Body = {};

	// Beam Base Request Declaration
	UPostServicesRegistrationsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PostServicesRegistrations",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bLocalOnly,_ServiceName,_RoutingKey,_Federation,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostServicesRegistrationsRequest* Make(FOptionalBool _bLocalOnly, FOptionalString _ServiceName, FOptionalString _RoutingKey, FOptionalSupportedFederation _Federation, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostServicesRegistrationsSuccess, FBeamRequestContext, Context, UPostServicesRegistrationsRequest*, Request, UServiceRegistrationResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostServicesRegistrationsError, FBeamRequestContext, Context, UPostServicesRegistrationsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostServicesRegistrationsComplete, FBeamRequestContext, Context, UPostServicesRegistrationsRequest*, Request);

using FPostServicesRegistrationsFullResponse = FBeamFullResponse<UPostServicesRegistrationsRequest*, UServiceRegistrationResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostServicesRegistrationsFullResponse, FPostServicesRegistrationsFullResponse);
