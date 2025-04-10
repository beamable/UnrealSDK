
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/TokenRequestWrapper.h"
#include "BeamableCore/Public/AutoGen/TokenResponse.h"

#include "AuthenticateRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UAuthenticateRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UTokenRequestWrapper* Body = {};

	// Beam Base Request Declaration
	UAuthenticateRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make Authenticate",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bCustomerScoped,_DeviceId,_ProviderService,_Token,_Code,_ExternalToken,_ChallengeSolution,_ProviderNamespace,_RedirectUri,_ThirdParty,_Context,_RefreshToken,_Username,_ClientId,_Password,_Scope,_InitProperties,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UAuthenticateRequest* Make(FString _GrantType, FOptionalBool _bCustomerScoped, FOptionalString _DeviceId, FOptionalString _ProviderService, FOptionalString _Token, FOptionalString _Code, FOptionalString _ExternalToken, FOptionalChallengeSolution _ChallengeSolution, FOptionalString _ProviderNamespace, FOptionalString _RedirectUri, FOptionalString _ThirdParty, FOptionalContextInfo _Context, FOptionalString _RefreshToken, FOptionalString _Username, FOptionalString _ClientId, FOptionalString _Password, FOptionalArrayOfString _Scope, FOptionalMapOfString _InitProperties, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnAuthenticateSuccess, FBeamRequestContext, Context, UAuthenticateRequest*, Request, UTokenResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnAuthenticateError, FBeamRequestContext, Context, UAuthenticateRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnAuthenticateComplete, FBeamRequestContext, Context, UAuthenticateRequest*, Request);

using FAuthenticateFullResponse = FBeamFullResponse<UAuthenticateRequest*, UTokenResponse*>;
DECLARE_DELEGATE_OneParam(FOnAuthenticateFullResponse, FAuthenticateFullResponse);
