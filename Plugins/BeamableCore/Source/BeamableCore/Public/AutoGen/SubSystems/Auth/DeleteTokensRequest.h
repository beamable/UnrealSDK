
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/AuthV2RevokeRefreshTokensRequestBody.h"
#include "BeamableCore/Public/AutoGen/AuthV2EmptyMessage.h"

#include "DeleteTokensRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteTokensRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAuthV2RevokeRefreshTokensRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteTokensRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make DeleteTokens",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteTokensRequest* Make(TArray<FString> _Tokens, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteTokensSuccess, FBeamRequestContext, Context, UDeleteTokensRequest*, Request, UAuthV2EmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteTokensError, FBeamRequestContext, Context, UDeleteTokensRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteTokensComplete, FBeamRequestContext, Context, UDeleteTokensRequest*, Request);

using FDeleteTokensFullResponse = FBeamFullResponse<UDeleteTokensRequest*, UAuthV2EmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnDeleteTokensFullResponse, FDeleteTokensFullResponse);
