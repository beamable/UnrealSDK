
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/MakeFriendshipRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PostFriendsMakeRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostFriendsMakeRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UMakeFriendshipRequestBody* Body;

	// Beam Base Request Declaration
	UPostFriendsMakeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostFriendsMakeRequest* MakePostFriendsMakeRequest(int64 _GamerTag, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFriendsMakeSuccess, FBeamRequestContext, Context, UPostFriendsMakeRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFriendsMakeError, FBeamRequestContext, Context, UPostFriendsMakeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostFriendsMakeComplete, FBeamRequestContext, Context, UPostFriendsMakeRequest*, Request);

using FPostFriendsMakeFullResponse = FBeamFullResponse<UPostFriendsMakeRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostFriendsMakeFullResponse, FPostFriendsMakeFullResponse);
