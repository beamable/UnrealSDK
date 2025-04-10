
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/SendFriendRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "DeleteFriendsInviteRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteFriendsInviteRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USendFriendRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteFriendsInviteRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Friends|Utils|Make/Break", DisplayName="Make DeleteFriendsInvite",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteFriendsInviteRequest* Make(FBeamGamerTag _GamerTag, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteFriendsInviteSuccess, FBeamRequestContext, Context, UDeleteFriendsInviteRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteFriendsInviteError, FBeamRequestContext, Context, UDeleteFriendsInviteRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteFriendsInviteComplete, FBeamRequestContext, Context, UDeleteFriendsInviteRequest*, Request);

using FDeleteFriendsInviteFullResponse = FBeamFullResponse<UDeleteFriendsInviteRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteFriendsInviteFullResponse, FDeleteFriendsInviteFullResponse);
