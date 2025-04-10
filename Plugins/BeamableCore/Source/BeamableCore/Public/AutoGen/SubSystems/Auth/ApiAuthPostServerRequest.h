
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/ServerTokenAuthRequestBody.h"
#include "BeamableCore/Public/AutoGen/ServerTokenResponse.h"

#include "ApiAuthPostServerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiAuthPostServerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UServerTokenAuthRequestBody* Body = {};

	// Beam Base Request Declaration
	UApiAuthPostServerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make ApiAuthPostServer",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_ClientId,_ClientSecret,_CustomerId,_RealmId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiAuthPostServerRequest* Make(FOptionalString _ClientId, FOptionalString _ClientSecret, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiAuthPostServerSuccess, FBeamRequestContext, Context, UApiAuthPostServerRequest*, Request, UServerTokenResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiAuthPostServerError, FBeamRequestContext, Context, UApiAuthPostServerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiAuthPostServerComplete, FBeamRequestContext, Context, UApiAuthPostServerRequest*, Request);

using FApiAuthPostServerFullResponse = FBeamFullResponse<UApiAuthPostServerRequest*, UServerTokenResponse*>;
DECLARE_DELEGATE_OneParam(FOnApiAuthPostServerFullResponse, FApiAuthPostServerFullResponse);
