
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UFacebookPaymentUpdateRequestBody* Body;

	// Beam Base Request Declaration
	UPostFacebookUpdateRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", DisplayName="Beam - Make PostFacebookUpdate",  meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostFacebookUpdateRequest* Make(FString _Object, TArray<UFacebookUpdatedEntry*> _Entry, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFacebookUpdateSuccess, FBeamRequestContext, Context, UPostFacebookUpdateRequest*, Request, UFacebookPaymentUpdateResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFacebookUpdateError, FBeamRequestContext, Context, UPostFacebookUpdateRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostFacebookUpdateComplete, FBeamRequestContext, Context, UPostFacebookUpdateRequest*, Request);

using FPostFacebookUpdateFullResponse = FBeamFullResponse<UPostFacebookUpdateRequest*, UFacebookPaymentUpdateResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostFacebookUpdateFullResponse, FPostFacebookUpdateFullResponse);
