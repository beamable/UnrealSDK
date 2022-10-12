
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/SteamAuthRequestBody.h"
#include "AutoGen/EmptyResponse.h"

#include "PostSteamAuthRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostSteamAuthRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	USteamAuthRequestBody* Body;

	// Beam Base Request Declaration
	UPostSteamAuthRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostSteamAuthRequest* MakePostSteamAuthRequest(FString _Ticket, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSteamAuthSuccess, FBeamRequestContext, Context, UPostSteamAuthRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSteamAuthError, FBeamRequestContext, Context, UPostSteamAuthRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostSteamAuthComplete, FBeamRequestContext, Context, UPostSteamAuthRequest*, Request);

using FPostSteamAuthFullResponse = FBeamFullResponse<UPostSteamAuthRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostSteamAuthFullResponse, FPostSteamAuthFullResponse);
