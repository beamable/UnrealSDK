
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "Serialization/BeamPlainTextResponseBody.h"

#include "GetFacebookUpdateRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetFacebookUpdateRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Hub Mode", Category="Beam")
	FString HubMode = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Hub Challenge", Category="Beam")
	FString HubChallenge = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Hub Verify Token", Category="Beam")
	FString HubVerifyToken = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetFacebookUpdateRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make GetFacebookUpdate",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetFacebookUpdateRequest* Make(FString _HubMode, FString _HubChallenge, FString _HubVerifyToken, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetFacebookUpdateSuccess, FBeamRequestContext, Context, UGetFacebookUpdateRequest*, Request, UBeamPlainTextResponseBody*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetFacebookUpdateError, FBeamRequestContext, Context, UGetFacebookUpdateRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetFacebookUpdateComplete, FBeamRequestContext, Context, UGetFacebookUpdateRequest*, Request);

using FGetFacebookUpdateFullResponse = FBeamFullResponse<UGetFacebookUpdateRequest*, UBeamPlainTextResponseBody*>;
DECLARE_DELEGATE_OneParam(FOnGetFacebookUpdateFullResponse, FGetFacebookUpdateFullResponse);
