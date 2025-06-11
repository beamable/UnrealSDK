
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/MicroserviceRegistrationRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "DeleteMicroserviceFederationTrafficRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteMicroserviceFederationTrafficRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UMicroserviceRegistrationRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteMicroserviceFederationTrafficRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make DeleteMicroserviceFederationTraffic",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bTrafficFilterEnabled,_RoutingKey,_Federation,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteMicroserviceFederationTrafficRequest* Make(FString _ServiceName, FOptionalBool _bTrafficFilterEnabled, FOptionalString _RoutingKey, FOptionalArrayOfSupportedFederation _Federation, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteMicroserviceFederationTrafficSuccess, FBeamRequestContext, Context, UDeleteMicroserviceFederationTrafficRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteMicroserviceFederationTrafficError, FBeamRequestContext, Context, UDeleteMicroserviceFederationTrafficRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteMicroserviceFederationTrafficComplete, FBeamRequestContext, Context, UDeleteMicroserviceFederationTrafficRequest*, Request);

using FDeleteMicroserviceFederationTrafficFullResponse = FBeamFullResponse<UDeleteMicroserviceFederationTrafficRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteMicroserviceFederationTrafficFullResponse, FDeleteMicroserviceFederationTrafficFullResponse);
