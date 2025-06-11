
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/GuestAuthRequestBody.h"
#include "BeamableCore/Public/AutoGen/AuthResponse.h"

#include "PostTokensGuestRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostTokensGuestRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGuestAuthRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostTokensGuestRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make PostTokensGuest",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Scope,_CustomerId,_RealmId,_Context,_InitProperties,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostTokensGuestRequest* Make(FOptionalString _Scope, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, FOptionalContextInfo _Context, FOptionalMapOfString _InitProperties, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTokensGuestSuccess, FBeamRequestContext, Context, UPostTokensGuestRequest*, Request, UAuthResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTokensGuestError, FBeamRequestContext, Context, UPostTokensGuestRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostTokensGuestComplete, FBeamRequestContext, Context, UPostTokensGuestRequest*, Request);

using FPostTokensGuestFullResponse = FBeamFullResponse<UPostTokensGuestRequest*, UAuthResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostTokensGuestFullResponse, FPostTokensGuestFullResponse);
