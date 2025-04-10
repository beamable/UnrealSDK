
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/RevokeTokenRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PutTokenRevokeRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutTokenRevokeRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	URevokeTokenRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutTokenRevokeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make PutTokenRevoke",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutTokenRevokeRequest* Make(FString _Token, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutTokenRevokeSuccess, FBeamRequestContext, Context, UPutTokenRevokeRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutTokenRevokeError, FBeamRequestContext, Context, UPutTokenRevokeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutTokenRevokeComplete, FBeamRequestContext, Context, UPutTokenRevokeRequest*, Request);

using FPutTokenRevokeFullResponse = FBeamFullResponse<UPutTokenRevokeRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutTokenRevokeFullResponse, FPutTokenRevokeFullResponse);
