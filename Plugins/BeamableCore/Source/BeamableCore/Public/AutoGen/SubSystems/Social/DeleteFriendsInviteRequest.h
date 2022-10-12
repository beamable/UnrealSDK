
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/SendFriendRequestBody.h"
#include "AutoGen/EmptyResponse.h"

#include "DeleteFriendsInviteRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteFriendsInviteRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	USendFriendRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteFriendsInviteRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UDeleteFriendsInviteRequest* MakeDeleteFriendsInviteRequest(int64 _GamerTag, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteFriendsInviteSuccess, FBeamRequestContext, Context, UDeleteFriendsInviteRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteFriendsInviteError, FBeamRequestContext, Context, UDeleteFriendsInviteRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteFriendsInviteComplete, FBeamRequestContext, Context, UDeleteFriendsInviteRequest*, Request);

using FDeleteFriendsInviteFullResponse = FBeamFullResponse<UDeleteFriendsInviteRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteFriendsInviteFullResponse, FDeleteFriendsInviteFullResponse);
