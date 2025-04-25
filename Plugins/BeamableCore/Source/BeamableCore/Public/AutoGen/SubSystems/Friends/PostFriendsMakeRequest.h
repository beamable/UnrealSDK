
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/MakeFriendshipRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

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
	UMakeFriendshipRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostFriendsMakeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Friends|Utils|Make/Break", DisplayName="Make PostFriendsMake",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostFriendsMakeRequest* Make(FBeamGamerTag _GamerTag, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFriendsMakeSuccess, FBeamRequestContext, Context, UPostFriendsMakeRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFriendsMakeError, FBeamRequestContext, Context, UPostFriendsMakeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostFriendsMakeComplete, FBeamRequestContext, Context, UPostFriendsMakeRequest*, Request);

using FPostFriendsMakeFullResponse = FBeamFullResponse<UPostFriendsMakeRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostFriendsMakeFullResponse, FPostFriendsMakeFullResponse);
