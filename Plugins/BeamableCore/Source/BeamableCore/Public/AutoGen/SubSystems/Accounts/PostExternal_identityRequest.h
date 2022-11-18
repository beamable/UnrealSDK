
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/ExternalIdentityRequestBody.h"
#include "AutoGen/AttachExternalIdentityApiResponse.h"

#include "PostExternal_identityRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostExternal_identityRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UExternalIdentityRequestBody* Body;

	// Beam Base Request Declaration
	UPostExternal_identityRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Accounts", DisplayName="Beam - Make PostExternal_identity",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_ChallengeSolution,RequestOwner"))
	static UPostExternal_identityRequest* Make(FString _ProviderAddress, FString _ExternalToken, FOptionalChallengeSolution _ChallengeSolution, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostExternal_identitySuccess, FBeamRequestContext, Context, UPostExternal_identityRequest*, Request, UAttachExternalIdentityApiResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostExternal_identityError, FBeamRequestContext, Context, UPostExternal_identityRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostExternal_identityComplete, FBeamRequestContext, Context, UPostExternal_identityRequest*, Request);

using FPostExternal_identityFullResponse = FBeamFullResponse<UPostExternal_identityRequest*, UAttachExternalIdentityApiResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostExternal_identityFullResponse, FPostExternal_identityFullResponse);
