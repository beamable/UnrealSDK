
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/PlayerIdRequestBody.h"
#include "AutoGen/FriendshipStatus.h"

#include "DeleteBlockedRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteBlockedRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UPlayerIdRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteBlockedRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UDeleteBlockedRequest* MakeDeleteBlockedRequest(FString _PlayerId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteBlockedSuccess, FBeamRequestContext, Context, UDeleteBlockedRequest*, Request, UFriendshipStatus*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteBlockedError, FBeamRequestContext, Context, UDeleteBlockedRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteBlockedComplete, FBeamRequestContext, Context, UDeleteBlockedRequest*, Request);

using FDeleteBlockedFullResponse = FBeamFullResponse<UDeleteBlockedRequest*, UFriendshipStatus*>;
DECLARE_DELEGATE_OneParam(FOnDeleteBlockedFullResponse, FDeleteBlockedFullResponse);