
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/AuthV2ExternalAuthRequestBody.h"
#include "BeamableCore/Public/AutoGen/AuthV2ExternalAuthResponse.h"

#include "PostTokensExternalRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostTokensExternalRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAuthV2ExternalAuthRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostTokensExternalRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make PostTokensExternal",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bHasProviderNamespace,_Provider,_ProviderNamespace,_Token,_ChallengeSolution,_Scope,_CustomerId,_RealmId,_Context,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostTokensExternalRequest* Make(FOptionalBool _bHasProviderNamespace, FOptionalString _Provider, FOptionalString _ProviderNamespace, FOptionalString _Token, FOptionalAuthV2ChallengeSolution _ChallengeSolution, FOptionalString _Scope, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, FOptionalAuthV2ContextInfo _Context, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTokensExternalSuccess, FBeamRequestContext, Context, UPostTokensExternalRequest*, Request, UAuthV2ExternalAuthResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTokensExternalError, FBeamRequestContext, Context, UPostTokensExternalRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostTokensExternalComplete, FBeamRequestContext, Context, UPostTokensExternalRequest*, Request);

using FPostTokensExternalFullResponse = FBeamFullResponse<UPostTokensExternalRequest*, UAuthV2ExternalAuthResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostTokensExternalFullResponse, FPostTokensExternalFullResponse);
