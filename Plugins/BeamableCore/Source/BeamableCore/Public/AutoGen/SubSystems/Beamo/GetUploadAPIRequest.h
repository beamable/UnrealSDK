
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/GetLambdaURI.h"

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

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make GetUploadAPI",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetUploadAPIRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetUploadAPISuccess, FBeamRequestContext, Context, UGetUploadAPIRequest*, Request, UGetLambdaURI*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetUploadAPIError, FBeamRequestContext, Context, UGetUploadAPIRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetUploadAPIComplete, FBeamRequestContext, Context, UGetUploadAPIRequest*, Request);

using FGetUploadAPIFullResponse = FBeamFullResponse<UGetUploadAPIRequest*, UGetLambdaURI*>;
DECLARE_DELEGATE_OneParam(FOnGetUploadAPIFullResponse, FGetUploadAPIFullResponse);
