
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/TokenRequestWrapper.h"
#include "AutoGen/TokenResponse.h"

#include "AuthenticateRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UAuthenticateRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UTokenRequestWrapper* Body;

	// Beam Base Request Declaration
	UAuthenticateRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_DeviceId,_Username,_Scope,_RefreshToken,_Context,_ThirdParty,_RedirectUri,_ClientId,_Code,_Token,_bCustomerScoped,_Password,Outer"))
	static UAuthenticateRequest* MakeAuthenticateRequest(FOptionalString _DeviceId, FOptionalString _Username, FOptionalArrayOfString _Scope, FOptionalString _RefreshToken, FOptionalContextInfo _Context, FOptionalString _ThirdParty, FOptionalString _RedirectUri, FOptionalString _ClientId, FOptionalString _Code, FOptionalString _Token, FOptionalBool _bCustomerScoped, FString _GrantType, FOptionalString _Password, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnAuthenticateSuccess, FBeamRequestContext, Context, UAuthenticateRequest*, Request, UTokenResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnAuthenticateError, FBeamRequestContext, Context, UAuthenticateRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnAuthenticateComplete, FBeamRequestContext, Context, UAuthenticateRequest*, Request);

using FAuthenticateFullResponse = FBeamFullResponse<UAuthenticateRequest*, UTokenResponse*>;
DECLARE_DELEGATE_OneParam(FOnAuthenticateFullResponse, FAuthenticateFullResponse);
