
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/MicroserviceRegistrationsQuery.h"
#include "BeamableCore/Public/AutoGen/MicroserviceRegistrationsResponse.h"

#include "PostMicroserviceRegistrationsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostMicroserviceRegistrationsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UMicroserviceRegistrationsQuery* Body = {};

	// Beam Base Request Declaration
	UPostMicroserviceRegistrationsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PostMicroserviceRegistrations",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bLocalOnly,_ServiceName,_RoutingKey,_Federation,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostMicroserviceRegistrationsRequest* Make(FOptionalBool _bLocalOnly, FOptionalString _ServiceName, FOptionalString _RoutingKey, FOptionalSupportedFederation _Federation, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostMicroserviceRegistrationsSuccess, FBeamRequestContext, Context, UPostMicroserviceRegistrationsRequest*, Request, UMicroserviceRegistrationsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostMicroserviceRegistrationsError, FBeamRequestContext, Context, UPostMicroserviceRegistrationsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostMicroserviceRegistrationsComplete, FBeamRequestContext, Context, UPostMicroserviceRegistrationsRequest*, Request);

using FPostMicroserviceRegistrationsFullResponse = FBeamFullResponse<UPostMicroserviceRegistrationsRequest*, UMicroserviceRegistrationsResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostMicroserviceRegistrationsFullResponse, FPostMicroserviceRegistrationsFullResponse);
