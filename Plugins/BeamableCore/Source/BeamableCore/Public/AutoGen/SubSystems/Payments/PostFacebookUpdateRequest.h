
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/FacebookPaymentUpdateRequestBody.h"
#include "Serialization/BeamPlainTextResponseBody.h"

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
	UFacebookPaymentUpdateRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostFacebookUpdateRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make PostFacebookUpdate",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostFacebookUpdateRequest* Make(FString _Object, TArray<UFacebookUpdatedEntry*> _Entry, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFacebookUpdateSuccess, FBeamRequestContext, Context, UPostFacebookUpdateRequest*, Request, UBeamPlainTextResponseBody*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFacebookUpdateError, FBeamRequestContext, Context, UPostFacebookUpdateRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostFacebookUpdateComplete, FBeamRequestContext, Context, UPostFacebookUpdateRequest*, Request);

using FPostFacebookUpdateFullResponse = FBeamFullResponse<UPostFacebookUpdateRequest*, UBeamPlainTextResponseBody*>;
DECLARE_DELEGATE_OneParam(FOnPostFacebookUpdateFullResponse, FPostFacebookUpdateFullResponse);
