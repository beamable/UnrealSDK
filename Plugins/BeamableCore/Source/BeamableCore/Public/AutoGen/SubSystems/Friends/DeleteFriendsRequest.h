
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/PlayerIdRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "DeleteFriendsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteFriendsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPlayerIdRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteFriendsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Friends|Utils|Make/Break", DisplayName="Make DeleteFriends",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteFriendsRequest* Make(FBeamGamerTag _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteFriendsSuccess, FBeamRequestContext, Context, UDeleteFriendsRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteFriendsError, FBeamRequestContext, Context, UDeleteFriendsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteFriendsComplete, FBeamRequestContext, Context, UDeleteFriendsRequest*, Request);

using FDeleteFriendsFullResponse = FBeamFullResponse<UDeleteFriendsRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteFriendsFullResponse, FDeleteFriendsFullResponse);
