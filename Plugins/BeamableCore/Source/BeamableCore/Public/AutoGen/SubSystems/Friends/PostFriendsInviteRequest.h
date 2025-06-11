
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/SendFriendRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "PostFriendsInviteRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostFriendsInviteRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USendFriendRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostFriendsInviteRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Friends|Utils|Make/Break", DisplayName="Make PostFriendsInvite",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostFriendsInviteRequest* Make(FBeamGamerTag _GamerTag, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFriendsInviteSuccess, FBeamRequestContext, Context, UPostFriendsInviteRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFriendsInviteError, FBeamRequestContext, Context, UPostFriendsInviteRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostFriendsInviteComplete, FBeamRequestContext, Context, UPostFriendsInviteRequest*, Request);

using FPostFriendsInviteFullResponse = FBeamFullResponse<UPostFriendsInviteRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostFriendsInviteFullResponse, FPostFriendsInviteFullResponse);
