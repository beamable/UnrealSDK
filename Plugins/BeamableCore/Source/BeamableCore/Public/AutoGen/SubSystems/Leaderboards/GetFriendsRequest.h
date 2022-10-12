
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/LeaderBoardViewResponse.h"

#include "GetFriendsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetFriendsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	FString ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetFriendsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetFriendsRequest* MakeGetFriendsRequest(FString _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetFriendsSuccess, FBeamRequestContext, Context, UGetFriendsRequest*, Request, ULeaderBoardViewResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetFriendsError, FBeamRequestContext, Context, UGetFriendsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetFriendsComplete, FBeamRequestContext, Context, UGetFriendsRequest*, Request);

using FGetFriendsFullResponse = FBeamFullResponse<UGetFriendsRequest*, ULeaderBoardViewResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetFriendsFullResponse, FGetFriendsFullResponse);
