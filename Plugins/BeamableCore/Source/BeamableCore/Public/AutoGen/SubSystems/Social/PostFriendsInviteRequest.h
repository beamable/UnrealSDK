
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/SendFriendRequestBody.h"
#include "AutoGen/EmptyResponse.h"

#include "PostFriendsInviteRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostFriendsInviteRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	USendFriendRequestBody* Body;

	// Beam Base Request Declaration
	UPostFriendsInviteRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostFriendsInviteRequest* MakePostFriendsInviteRequest(int64 _GamerTag, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFriendsInviteSuccess, FBeamRequestContext, Context, UPostFriendsInviteRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFriendsInviteError, FBeamRequestContext, Context, UPostFriendsInviteRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostFriendsInviteComplete, FBeamRequestContext, Context, UPostFriendsInviteRequest*, Request);

using FPostFriendsInviteFullResponse = FBeamFullResponse<UPostFriendsInviteRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostFriendsInviteFullResponse, FPostFriendsInviteFullResponse);
