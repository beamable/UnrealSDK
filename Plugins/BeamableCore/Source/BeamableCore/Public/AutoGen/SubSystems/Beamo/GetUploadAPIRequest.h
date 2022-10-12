
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/GetLambdaURI.h"

#include "GetUploadAPIRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetUploadAPIRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetUploadAPIRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetUploadAPIRequest* MakeGetUploadAPIRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetUploadAPISuccess, FBeamRequestContext, Context, UGetUploadAPIRequest*, Request, UGetLambdaURI*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetUploadAPIError, FBeamRequestContext, Context, UGetUploadAPIRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetUploadAPIComplete, FBeamRequestContext, Context, UGetUploadAPIRequest*, Request);

using FGetUploadAPIFullResponse = FBeamFullResponse<UGetUploadAPIRequest*, UGetLambdaURI*>;
DECLARE_DELEGATE_OneParam(FOnGetUploadAPIFullResponse, FGetUploadAPIFullResponse);
