
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/AttachExternalIdentityApiRequestBody.h"
#include "BeamableCore/Public/AutoGen/AttachExternalIdentityApiResponse.h"

#include "PostExternalIdentityRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostExternalIdentityRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAttachExternalIdentityApiRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostExternalIdentityRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make PostExternalIdentity",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_ChallengeSolution,_ProviderNamespace,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostExternalIdentityRequest* Make(FString _ProviderService, FString _ExternalToken, FOptionalChallengeSolution _ChallengeSolution, FOptionalString _ProviderNamespace, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostExternalIdentitySuccess, FBeamRequestContext, Context, UPostExternalIdentityRequest*, Request, UAttachExternalIdentityApiResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostExternalIdentityError, FBeamRequestContext, Context, UPostExternalIdentityRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostExternalIdentityComplete, FBeamRequestContext, Context, UPostExternalIdentityRequest*, Request);

using FPostExternalIdentityFullResponse = FBeamFullResponse<UPostExternalIdentityRequest*, UAttachExternalIdentityApiResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostExternalIdentityFullResponse, FPostExternalIdentityFullResponse);
