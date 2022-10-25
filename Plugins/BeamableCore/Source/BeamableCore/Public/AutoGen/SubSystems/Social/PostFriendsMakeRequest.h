
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UMakeFriendshipRequestBody* Body;

	// Beam Base Request Declaration
	UPostFriendsMakeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Social", DisplayName="Beam - Make PostFriendsMake",  meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostFriendsMakeRequest* Make(int64 _GamerTag, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFriendsMakeSuccess, FBeamRequestContext, Context, UPostFriendsMakeRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFriendsMakeError, FBeamRequestContext, Context, UPostFriendsMakeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostFriendsMakeComplete, FBeamRequestContext, Context, UPostFriendsMakeRequest*, Request);

using FPostFriendsMakeFullResponse = FBeamFullResponse<UPostFriendsMakeRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostFriendsMakeFullResponse, FPostFriendsMakeFullResponse);
