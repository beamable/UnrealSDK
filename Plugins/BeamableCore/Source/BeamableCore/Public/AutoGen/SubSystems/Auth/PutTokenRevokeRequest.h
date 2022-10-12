
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/RevokeTokenRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PutTokenRevokeRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutTokenRevokeRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	URevokeTokenRequestBody* Body;

	// Beam Base Request Declaration
	UPutTokenRevokeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPutTokenRevokeRequest* MakePutTokenRevokeRequest(FString _Token, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutTokenRevokeSuccess, FBeamRequestContext, Context, UPutTokenRevokeRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutTokenRevokeError, FBeamRequestContext, Context, UPutTokenRevokeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutTokenRevokeComplete, FBeamRequestContext, Context, UPutTokenRevokeRequest*, Request);

using FPutTokenRevokeFullResponse = FBeamFullResponse<UPutTokenRevokeRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutTokenRevokeFullResponse, FPutTokenRevokeFullResponse);
