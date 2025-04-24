
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/DeleteExternalIdentityApiRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "DeleteExternalIdentityRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteExternalIdentityRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UDeleteExternalIdentityApiRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteExternalIdentityRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make DeleteExternalIdentity",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_ProviderNamespace,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteExternalIdentityRequest* Make(FString _ProviderService, FString _UserId, FOptionalString _ProviderNamespace, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteExternalIdentitySuccess, FBeamRequestContext, Context, UDeleteExternalIdentityRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteExternalIdentityError, FBeamRequestContext, Context, UDeleteExternalIdentityRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteExternalIdentityComplete, FBeamRequestContext, Context, UDeleteExternalIdentityRequest*, Request);

using FDeleteExternalIdentityFullResponse = FBeamFullResponse<UDeleteExternalIdentityRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteExternalIdentityFullResponse, FDeleteExternalIdentityFullResponse);
