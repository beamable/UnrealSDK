
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/GetSocialStatusesResponse.h"

#include "BasicFriendsGetFriendsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicFriendsGetFriendsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Ids", Category="Beam")
	TArray<FString> PlayerIds = {};

	// Body Params
	

	// Beam Base Request Declaration
	UBasicFriendsGetFriendsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Friends|Utils|Make/Break", DisplayName="Make BasicFriendsGetFriends",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicFriendsGetFriendsRequest* Make(TArray<FString> _PlayerIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicFriendsGetFriendsSuccess, FBeamRequestContext, Context, UBasicFriendsGetFriendsRequest*, Request, UGetSocialStatusesResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicFriendsGetFriendsError, FBeamRequestContext, Context, UBasicFriendsGetFriendsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicFriendsGetFriendsComplete, FBeamRequestContext, Context, UBasicFriendsGetFriendsRequest*, Request);

using FBasicFriendsGetFriendsFullResponse = FBeamFullResponse<UBasicFriendsGetFriendsRequest*, UGetSocialStatusesResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicFriendsGetFriendsFullResponse, FBasicFriendsGetFriendsFullResponse);
