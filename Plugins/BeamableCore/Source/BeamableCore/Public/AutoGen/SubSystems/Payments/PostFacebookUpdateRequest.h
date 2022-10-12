
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/FacebookPaymentUpdateRequestBody.h"
#include "AutoGen/FacebookPaymentUpdateResponse.h"

#include "PostFacebookUpdateRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostFacebookUpdateRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UFacebookPaymentUpdateRequestBody* Body;

	// Beam Base Request Declaration
	UPostFacebookUpdateRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostFacebookUpdateRequest* MakePostFacebookUpdateRequest(FString _Object, TArray<UFacebookUpdatedEntry*> _Entry, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFacebookUpdateSuccess, FBeamRequestContext, Context, UPostFacebookUpdateRequest*, Request, UFacebookPaymentUpdateResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFacebookUpdateError, FBeamRequestContext, Context, UPostFacebookUpdateRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostFacebookUpdateComplete, FBeamRequestContext, Context, UPostFacebookUpdateRequest*, Request);

using FPostFacebookUpdateFullResponse = FBeamFullResponse<UPostFacebookUpdateRequest*, UFacebookPaymentUpdateResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostFacebookUpdateFullResponse, FPostFacebookUpdateFullResponse);
